//=- fox32ISelDAGToDAG.cpp - A dag to dag inst selector for fox32 -===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the fox32 target.
//
//===----------------------------------------------------------------------===//

#include "fox32ISelDAGToDAG.h"
#include "MCTargetDesc/fox32MCTargetDesc.h"
#include "fox32ISelLowering.h"
#include "llvm/Support/KnownBits.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-isel"

void fox32DAGToDAGISel::Select(SDNode *Node) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  // If we have a custom node, we have already selected.
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(dbgs() << "== "; Node->dump(CurDAG); dbgs() << "\n");
    Node->setNodeId(-1);
    return;
  }

  // Instruction Selection not handled by the auto-generated tablegen selection
  // should be handled here.
  unsigned Opcode = Node->getOpcode();
  MVT GRLenVT = Subtarget->getGRLenVT();
  SDLoc DL(Node);
  MVT VT = Node->getSimpleValueType(0);

  switch (Opcode) {
  default:
    break;
  case ISD::Constant: {
    int64_t Imm = cast<ConstantSDNode>(Node)->getSExtValue();
    if (Imm == 0 && VT == GRLenVT) {
      SDValue New = CurDAG->getCopyFromReg(CurDAG->getEntryNode(), DL,
                                           fox32::X0, GRLenVT);
      ReplaceNode(Node, New.getNode());
      return;
    }
    SDNode *Result = nullptr;
    SDValue SrcReg = CurDAG->getRegister(fox32::X0, GRLenVT);
    // The instructions in the sequence are handled here.
    // TODO
    /*
    for (fox32MatInt::Inst &Inst : fox32MatInt::generateInstSeq(Imm)) {
      SDValue SDImm = CurDAG->getTargetConstant(Inst.Imm, DL, GRLenVT);

      // TODO
      if (Inst.Opc == fox32::LU12I_W)
        Result = CurDAG->getMachineNode(fox32::LU12I_W, DL, GRLenVT, SDImm);
      else
        Result = CurDAG->getMachineNode(Inst.Opc, DL, GRLenVT, SrcReg, SDImm);

      SrcReg = SDValue(Result, 0);
    }
    */

    ReplaceNode(Node, Result);
    return;
  }
  case ISD::FrameIndex: {
    SDValue Imm = CurDAG->getTargetConstant(0, DL, GRLenVT);
    int FI = cast<FrameIndexSDNode>(Node)->getIndex();
    SDValue TFI = CurDAG->getTargetFrameIndex(FI, VT);
    return;
  }
    // TODO: Add selection nodes needed later.
  }

  // Select the default instruction.
  SelectCode(Node);
}

bool fox32DAGToDAGISel::SelectBaseAddr(SDValue Addr, SDValue &Base) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  // If this is FrameIndex, select it directly. Otherwise just let it get
  // selected to a register independently.
  if (auto *FIN = dyn_cast<FrameIndexSDNode>(Addr))
    Base =
        CurDAG->getTargetFrameIndex(FIN->getIndex(), Subtarget->getGRLenVT());
  else
    Base = Addr;
  return true;
}

bool fox32DAGToDAGISel::selectShiftMask(SDValue N, unsigned ShiftWidth,
                                        SDValue &ShAmt) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  // Shift instructions on fox32 only read the lower 5 or 6 bits of the
  // shift amount. If there is an AND on the shift amount, we can bypass it if
  // it doesn't affect any of those bits.
  if (N.getOpcode() == ISD::AND && isa<ConstantSDNode>(N.getOperand(1))) {
    const APInt &AndMask = N->getConstantOperandAPInt(1);

    // Since the max shift amount is a power of 2 we can subtract 1 to make a
    // mask that covers the bits needed to represent all shift amounts.
    assert(isPowerOf2_32(ShiftWidth) && "Unexpected max shift amount!");
    APInt ShMask(AndMask.getBitWidth(), ShiftWidth - 1);

    if (ShMask.isSubsetOf(AndMask)) {
      ShAmt = N.getOperand(0);
      return true;
    }

    // SimplifyDemandedBits may have optimized the mask so try restoring any
    // bits that are known zero.
    KnownBits Known = CurDAG->computeKnownBits(N->getOperand(0));
    if (ShMask.isSubsetOf(AndMask | Known.Zero)) {
      ShAmt = N.getOperand(0);
      return true;
    }
  } else if (N.getOpcode() == fox32ISD::BSTRPICK) {
    // Similar to the above AND, if there is a BSTRPICK on the shift amount, we
    // can bypass it.
    assert(isPowerOf2_32(ShiftWidth) && "Unexpected max shift amount!");
    assert(isa<ConstantSDNode>(N.getOperand(1)) && "Illegal msb operand!");
    assert(isa<ConstantSDNode>(N.getOperand(2)) && "Illegal lsb operand!");
    uint64_t msb = N.getConstantOperandVal(1), lsb = N.getConstantOperandVal(2);
    if (lsb == 0 && Log2_32(ShiftWidth) <= msb + 1) {
      ShAmt = N.getOperand(0);
      return true;
    }
  } else if (N.getOpcode() == ISD::SUB &&
             isa<ConstantSDNode>(N.getOperand(0))) {
    uint64_t Imm = N.getConstantOperandVal(0);
  }

  ShAmt = N;
  return true;
}

bool fox32DAGToDAGISel::selectSExti32(SDValue N, SDValue &Val) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  if (N.getOpcode() == ISD::SIGN_EXTEND_INREG &&
      cast<VTSDNode>(N.getOperand(1))->getVT() == MVT::i32) {
    Val = N.getOperand(0);
    return true;
  }
  MVT VT = N.getSimpleValueType();
  if (CurDAG->ComputeNumSignBits(N) > (VT.getSizeInBits() - 32)) {
    Val = N;
    return true;
  }

  return false;
}

bool fox32DAGToDAGISel::selectZExti32(SDValue N, SDValue &Val) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  if (N.getOpcode() == ISD::AND) {
    auto *C = dyn_cast<ConstantSDNode>(N.getOperand(1));
    if (C && C->getZExtValue() == UINT64_C(0xFFFFFFFF)) {
      Val = N.getOperand(0);
      return true;
    }
  }
  MVT VT = N.getSimpleValueType();
  APInt Mask = APInt::getHighBitsSet(VT.getSizeInBits(), 32);
  if (CurDAG->MaskedValueIsZero(N, Mask)) {
    Val = N;
    return true;
  }

  return false;
}

// This pass converts a legalized DAG into a fox32-specific DAG, ready
// for instruction scheduling.
FunctionPass *llvm::createfox32ISelDag(fox32TargetMachine &TM) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  return new fox32DAGToDAGISel(TM);
}
