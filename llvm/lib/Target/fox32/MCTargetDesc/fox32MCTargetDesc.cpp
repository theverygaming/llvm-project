//===-- fox32MCTargetDesc.cpp - fox32 Target Descriptions ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides fox32 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/fox32TargetInfo.h"
#include "fox32.h"
#include "fox32InstPrinter.h"
#include "fox32MCAsmInfo.h"

#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/MC/TargetRegistry.h"

#define GET_REGINFO_ENUM
#define GET_REGINFO_MC_DESC
#include "fox32GenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "fox32GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "fox32GenSubtargetInfo.inc"

using namespace llvm;

static MCRegisterInfo *createfox32MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  Initfox32MCRegisterInfo(
      X, fox32::X1); // TODO: figure out why this needs the register passed???
  return X;
}

static MCInstrInfo *createfox32MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  Initfox32MCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *
createfox32MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  if (CPU.empty()) {
    CPU = "fox32";
  }
  return createfox32MCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createfox32MCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new fox32MCAsmInfo(TT);

  // TODO
  // Initial state of the frame pointer is sp(r3).
  // MCRegister SP = MRI.getDwarfRegNum(fox32::R3, true);
  // MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  // MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstPrinter *createfox32MCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new fox32InstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializefox32TargetMC() {
  for (Target *T : {&getThefox32Target()}) {
    TargetRegistry::RegisterMCRegInfo(*T, createfox32MCRegisterInfo);
    TargetRegistry::RegisterMCInstrInfo(*T, createfox32MCInstrInfo);
    TargetRegistry::RegisterMCSubtargetInfo(*T, createfox32MCSubtargetInfo);
    TargetRegistry::RegisterMCAsmInfo(*T, createfox32MCAsmInfo);
    TargetRegistry::RegisterMCInstPrinter(*T, createfox32MCInstPrinter);
  }
}
