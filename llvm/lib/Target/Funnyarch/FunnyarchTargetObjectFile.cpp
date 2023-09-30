//===-- FunnyarchTargetObjectFile.cpp - Funnyarch Object Files --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "FunnyarchTargetObjectFile.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

void
FunnyarchTargetObjectFile::Initialize(MCContext &Ctx, const TargetMachine &TM) {
  TargetLoweringObjectFileELF::Initialize(Ctx, TM);
}
