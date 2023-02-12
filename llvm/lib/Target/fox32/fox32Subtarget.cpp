//===-- fox32Subtarget.cpp - fox32 Subtarget Information -*- C++ -*--=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the fox32 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "fox32Subtarget.h"
#include "fox32FrameLowering.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "fox32GenSubtargetInfo.inc"

void fox32Subtarget::anchor() {}

fox32Subtarget &
fox32Subtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                                StringRef FS) {
  if (CPU.empty())
    CPU = "generic-fox32";

  ParseSubtargetFeatures(CPU, CPU, FS);

  // TODO: ILP32{S,F} LP64{S,F}
  // TODO:
  printf("TODO: %s:%d\n", __FILE__, __LINE__);
  // TargetABI = fox32ABI::ABI_ILP32D;
  return *this;
}

fox32Subtarget::fox32Subtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : fox32GenSubtargetInfo(TT, CPU, CPU, FS),
      FrameLowering(initializeSubtargetDependencies(TT, CPU, FS)),
      InstrInfo(*this), RegInfo(getHwMode()), TLInfo(TM, *this) {}
