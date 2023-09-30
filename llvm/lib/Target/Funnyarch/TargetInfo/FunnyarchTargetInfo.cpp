//===-- FunnyarchTargetInfo.cpp - Funnyarch Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/FunnyarchTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheFunnyarchTarget() {
  static Target TheFunnyarchTarget;
  return TheFunnyarchTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFunnyarchTargetInfo() {
  RegisterTarget<Triple::funnyarch> X(getTheFunnyarchTarget(), "funnyarch",
                                  "32-bit RISC-V", "Funnyarch");
}
