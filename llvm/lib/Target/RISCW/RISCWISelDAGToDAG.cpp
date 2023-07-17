//===-- RISCWISelDAGToDAG.cpp - A Dag to Dag Inst Selector for RISCW ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the RISCW target.
//
//===----------------------------------------------------------------------===//

#include "RISCWISelDAGToDAG.h"
#include "RISCWSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

#define DEBUG_TYPE "riscw-isel"

bool RISCWDAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &static_cast<const RISCWSubtarget &>(MF.getSubtarget());
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void RISCWDAGToDAGISel::Select(SDNode *Node) {
  // If we have a custom node, we already have selected!
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(errs() << "== "; Node->dump(CurDAG); errs() << "\n");
    Node->setNodeId(-1);
    return;
  }

  // Instruction Selection not handled by the auto-generated tablegen selection
  // should be handled here.
  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  switch(Opcode) {
  case ISD::Constant: {
    auto ConstNode = cast<ConstantSDNode>(Node);
    if (ConstNode->isNullValue()) {
      SDValue New = CurDAG->getCopyFromReg(CurDAG->getEntryNode(), SDLoc(Node),
                                           RISCW::X0, MVT::i32);
      ReplaceNode(Node, New.getNode());
      return;
    }
    break;
  }
  default: break;
  }

  // Select the default instruction
  SelectCode(Node);
}
