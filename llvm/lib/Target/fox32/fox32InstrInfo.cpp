//=- fox32InstrInfo.cpp - fox32 Instruction Information -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the fox32 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "fox32InstrInfo.h"
#include "fox32.h"
#include "fox32MachineFunctionInfo.h"
#include "fox32RegisterInfo.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "fox32GenInstrInfo.inc"

fox32InstrInfo::fox32InstrInfo(fox32Subtarget &STI) : fox32GenInstrInfo() {}

void fox32InstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator MBBI,
                                 const DebugLoc &DL, MCRegister DstReg,
                                 MCRegister SrcReg, bool KillSrc) const {
  printf("UNIMPLEMENTED %s:%s:%d\n", __func__, __FILE__, __LINE__);
}

void fox32InstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator I,
                                         Register SrcReg, bool IsKill, int FI,
                                         const TargetRegisterClass *RC,
                                         const TargetRegisterInfo *TRI) const {
  printf("UNIMPLEMENTED %s:%s:%d\n", __func__, __FILE__, __LINE__);
}

void fox32InstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                          MachineBasicBlock::iterator I,
                                          Register DstReg, int FI,
                                          const TargetRegisterClass *RC,
                                          const TargetRegisterInfo *TRI) const {
  printf("UNIMPLEMENTED %s:%s:%d\n", __func__, __FILE__, __LINE__);
}
