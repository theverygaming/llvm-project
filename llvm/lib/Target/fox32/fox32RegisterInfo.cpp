//===- fox32RegisterInfo.cpp - fox32 Register Information -*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the fox32 implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#include "fox32RegisterInfo.h"
#include "fox32.h"
#include "fox32Subtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_ENUM
#define GET_REGINFO_TARGET_DESC
#include "fox32GenRegisterInfo.inc"

using namespace llvm;

fox32RegisterInfo::fox32RegisterInfo(unsigned HwMode)
    : fox32GenRegisterInfo(fox32::X1, /*DwarfFlavour*/ 0,
                           /*EHFlavor*/ 0,
                           /*PC*/ 0, HwMode) {}

const MCPhysReg *
fox32RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  auto &Subtarget = MF->getSubtarget<fox32Subtarget>();

  printf("UNIMPLEMENTED %s:%s:%d\n", __func__, __FILE__, __LINE__);
  return nullptr;
}

const uint32_t *
fox32RegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID CC) const {
  auto &Subtarget = MF.getSubtarget<fox32Subtarget>();

  printf("UNIMPLEMENTED %s:%s:%d\n", __func__, __FILE__, __LINE__);
  return nullptr;
}

const uint32_t *fox32RegisterInfo::getNoPreservedMask() const {
  printf("UNIMPLEMENTED %s:%s:%d\n", __func__, __FILE__, __LINE__);
  return nullptr;
}

BitVector fox32RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  const fox32FrameLowering *TFI = getFrameLowering(MF);
  BitVector Reserved(getNumRegs());

  // Use markSuperRegs to ensure any register aliases are also reserved
  markSuperRegs(Reserved, fox32::X0);  // zero
  markSuperRegs(Reserved, fox32::X2);  // tp
  markSuperRegs(Reserved, fox32::X3);  // sp
  markSuperRegs(Reserved, fox32::X21); // non-allocatable
  if (TFI->hasFP(MF))
    markSuperRegs(Reserved, fox32::X22); // fp
  // Reserve the base register if we need to realign the stack and allocate
  // variable-sized objects at runtime.
  // if (TFI->hasBP(MF))
  //  markSuperRegs(Reserved, fox32ABI::getBPReg()); // bp

  assert(checkAllSuperRegsMarked(Reserved));
  return Reserved;
}

bool fox32RegisterInfo::isConstantPhysReg(MCRegister PhysReg) const {
  return PhysReg == fox32::X0;
}

Register fox32RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? fox32::X22 : fox32::X3;
}

void fox32RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  // TODO: this implementation is a temporary placeholder which does just
  // enough to allow other aspects of code generation to be tested.

  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  StackOffset Offset =
      TFI->getFrameIndexReference(MF, FrameIndex, FrameReg) +
      StackOffset::getFixed(MI.getOperand(FIOperandNum + 1).getImm());

  // Offsets must be encodable with a 12-bit immediate field.
  if (!isInt<12>(Offset.getFixed())) {
    report_fatal_error("Frame offsets outside of the signed 12-bit range is "
                       "not supported currently");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset.getFixed());
}
