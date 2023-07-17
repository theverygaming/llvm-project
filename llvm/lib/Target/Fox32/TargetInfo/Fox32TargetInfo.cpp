//===-- Fox32TargetInfo.cpp - Fox32 Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/Fox32TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheFox32Target() {
  static Target TheFox32Target;
  return TheFox32Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFox32TargetInfo() {
  RegisterTarget<Triple::fox32> X(getTheFox32Target(), "fox32",
                                  "32-bit RISC-V", "Fox32");
}
