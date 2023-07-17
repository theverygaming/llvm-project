//===-- Fox32Subtarget.cpp - Fox32 Subtarget Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Fox32 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "Fox32.h"
#include "Fox32Subtarget.h"
#include "Fox32MachineFunction.h"
#include "Fox32RegisterInfo.h"
#include "Fox32TargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "Fox32GenSubtargetInfo.inc"

Fox32Subtarget::Fox32Subtarget(const Triple &TT, StringRef CPU, StringRef FS, const Fox32TargetMachine &TM)
      : Fox32GenSubtargetInfo(TT, CPU, CPU, FS),
      TSInfo(),
      InstrInfo(initializeSubtargetDependencies(TT, CPU, CPU, FS)),
      FrameLowering(*this),
      TLInfo(TM, *this),
      RegInfo(*this) { }


Fox32Subtarget &
Fox32Subtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU, StringRef TuneCPU,
                                                StringRef FS) {
  std::string CPUName = CPU.str();
  if (CPUName.empty())
    CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, CPUName, FS);

  return *this;
}
