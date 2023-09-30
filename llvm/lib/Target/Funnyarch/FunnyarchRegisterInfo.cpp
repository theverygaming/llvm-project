//===-- FunnyarchRegisterInfo.cpp - Funnyarch Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Funnyarch implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "FunnyarchRegisterInfo.h"
#include "FunnyarchSubtarget.h"
#include "llvm/Support/Debug.h"

#define GET_REGINFO_TARGET_DESC
#include "FunnyarchGenRegisterInfo.inc"

#define DEBUG_TYPE "funnyarch-reginfo"

using namespace llvm;

FunnyarchRegisterInfo::FunnyarchRegisterInfo(const FunnyarchSubtarget &ST)
  : FunnyarchGenRegisterInfo(Funnyarch::R1, /*DwarfFlavour*/0, /*EHFlavor*/0,
                         /*PC*/0), Subtarget(ST) {}

const MCPhysReg *
FunnyarchRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return Funnyarch_CalleeSavedRegs_SaveList;
}

const TargetRegisterClass *FunnyarchRegisterInfo::intRegClass(unsigned Size) const {
  return &Funnyarch::GPRRegClass;
}

const uint32_t *
FunnyarchRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID) const {
  return Funnyarch_CalleeSavedRegs_RegMask;
}

BitVector FunnyarchRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  markSuperRegs(Reserved, Funnyarch::RSP); 
  markSuperRegs(Reserved, Funnyarch::RESP); 
  markSuperRegs(Reserved, Funnyarch::RFP);

  return Reserved;
}

void FunnyarchRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj,
                                           unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  llvm_unreachable("Unsupported eliminateFrameIndex");
}

bool
FunnyarchRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
FunnyarchRegisterInfo::requiresFrameIndexScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
FunnyarchRegisterInfo::requiresFrameIndexReplacementScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
FunnyarchRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

Register FunnyarchRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  llvm_unreachable("Unsupported getFrameRegister");
}

