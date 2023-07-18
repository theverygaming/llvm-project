//===-- Fox32RegisterInfo.cpp - Fox32 Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Fox32 implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "Fox32RegisterInfo.h"
#include "Fox32Subtarget.h"
#include "llvm/Support/Debug.h"

#define GET_REGINFO_TARGET_DESC
#include "Fox32GenRegisterInfo.inc"

#define DEBUG_TYPE "fox32-reginfo"

using namespace llvm;

Fox32RegisterInfo::Fox32RegisterInfo(const Fox32Subtarget &ST)
  : Fox32GenRegisterInfo(Fox32::R1, /*DwarfFlavour*/0, /*EHFlavor*/0,
                         /*PC*/0), Subtarget(ST) {}

const MCPhysReg *
Fox32RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return Fox32_CalleeSavedRegs_SaveList;
}

const TargetRegisterClass *Fox32RegisterInfo::intRegClass(unsigned Size) const {
  return &Fox32::GPRRegClass;
}

const uint32_t *
Fox32RegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID) const {
  return Fox32_CalleeSavedRegs_RegMask;
}

BitVector Fox32RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  markSuperRegs(Reserved, Fox32::RSP); 
  markSuperRegs(Reserved, Fox32::RESP); 
  markSuperRegs(Reserved, Fox32::RFP);

  return Reserved;
}

void Fox32RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj,
                                           unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  llvm_unreachable("Unsupported eliminateFrameIndex");
}

bool
Fox32RegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
Fox32RegisterInfo::requiresFrameIndexScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
Fox32RegisterInfo::requiresFrameIndexReplacementScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
Fox32RegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

Register Fox32RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  llvm_unreachable("Unsupported getFrameRegister");
}

