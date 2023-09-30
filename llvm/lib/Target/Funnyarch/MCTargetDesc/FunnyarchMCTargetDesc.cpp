//===-- FunnyarchMCTargetDesc.cpp - Funnyarch Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Funnyarch specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "FunnyarchMCTargetDesc.h"
#include "FunnyarchInstPrinter.h"
#include "FunnyarchMCAsmInfo.h"
#include "TargetInfo/FunnyarchTargetInfo.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "FunnyarchGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "FunnyarchGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "FunnyarchGenRegisterInfo.inc"

static MCInstrInfo *createFunnyarchMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitFunnyarchMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createFunnyarchMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}

static MCSubtargetInfo *
createFunnyarchMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  std::string CPUName = CPU.str();
  if (CPUName.empty())
    CPUName = "generic";
  return createFunnyarchMCSubtargetInfoImpl(TT, CPUName, /*TuneCPU*/ CPUName, FS);
}

static MCInstPrinter *createFunnyarchMCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new FunnyarchInstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createFunnyarchMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new FunnyarchMCAsmInfo(TT);

  unsigned WP = MRI.getDwarfRegNum(Funnyarch::R2, true);
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfaRegister(nullptr, WP);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

extern "C" void LLVMInitializeFunnyarchTargetMC() {
  for (Target *T : {&getTheFunnyarchTarget()}) {
    // Register the MC asm info.
    TargetRegistry::RegisterMCAsmInfo(*T, createFunnyarchMCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createFunnyarchMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createFunnyarchMCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T, createFunnyarchMCSubtargetInfo);

    // Register the code emitter.
    TargetRegistry::RegisterMCCodeEmitter(*T, createFunnyarchMCCodeEmitter);

    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCInstPrinter(*T, createFunnyarchMCInstPrinter);

    // Register the asm backend.
    TargetRegistry::RegisterMCAsmBackend(*T, createFunnyarchAsmBackend);
  }
}
