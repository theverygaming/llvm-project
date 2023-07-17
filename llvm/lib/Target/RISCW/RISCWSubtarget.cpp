//===-- RISCWSubtarget.cpp - RISCW Subtarget Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the RISCW specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "RISCW.h"
#include "RISCWSubtarget.h"
#include "RISCWMachineFunction.h"
#include "RISCWRegisterInfo.h"
#include "RISCWTargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "riscw-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RISCWGenSubtargetInfo.inc"

RISCWSubtarget::RISCWSubtarget(const Triple &TT, StringRef CPU, StringRef FS, const RISCWTargetMachine &TM)
      : RISCWGenSubtargetInfo(TT, CPU, CPU, FS),
      TSInfo(),
      InstrInfo(initializeSubtargetDependencies(TT, CPU, CPU, FS)),
      FrameLowering(*this),
      TLInfo(TM, *this),
      RegInfo(*this) { }


RISCWSubtarget &
RISCWSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU, StringRef TuneCPU,
                                                StringRef FS) {
  std::string CPUName = CPU.str();
  if (CPUName.empty())
    CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, CPUName, FS);

  return *this;
}
