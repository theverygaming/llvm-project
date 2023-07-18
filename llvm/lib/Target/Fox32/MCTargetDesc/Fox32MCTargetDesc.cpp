//===-- Fox32MCTargetDesc.cpp - Fox32 Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Fox32 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "Fox32MCTargetDesc.h"
#include "Fox32InstPrinter.h"
#include "Fox32MCAsmInfo.h"
#include "TargetInfo/Fox32TargetInfo.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "Fox32GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "Fox32GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Fox32GenRegisterInfo.inc"

static MCInstrInfo *createFox32MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitFox32MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createFox32MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}

static MCSubtargetInfo *
createFox32MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  std::string CPUName = CPU.str();
  if (CPUName.empty())
    CPUName = "generic";
  return createFox32MCSubtargetInfoImpl(TT, CPUName, /*TuneCPU*/ CPUName, FS);
}

static MCInstPrinter *createFox32MCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new Fox32InstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createFox32MCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new Fox32MCAsmInfo(TT);

  unsigned WP = MRI.getDwarfRegNum(Fox32::R2, true);
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfaRegister(nullptr, WP);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

extern "C" void LLVMInitializeFox32TargetMC() {
  for (Target *T : {&getTheFox32Target()}) {
    // Register the MC asm info.
    TargetRegistry::RegisterMCAsmInfo(*T, createFox32MCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createFox32MCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createFox32MCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T, createFox32MCSubtargetInfo);

    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCInstPrinter(*T, createFox32MCInstPrinter);
  }
}
