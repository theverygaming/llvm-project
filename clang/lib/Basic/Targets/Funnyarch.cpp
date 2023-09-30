//===--- Funnyarch.cpp - Implement Funnyarch target feature support ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements FunnyarchTargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Funnyarch.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

const char *const FunnyarchTargetInfo::GCCRegNames[] = {
  // Integer registers
  "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
  "r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",
  "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
  "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
};

const TargetInfo::GCCRegAlias GCCRegAliases[] = {{{"sp"}, "rsp"}, {{"fp"}, "rfp"}};

ArrayRef<const char *> FunnyarchTargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

ArrayRef<TargetInfo::GCCRegAlias> FunnyarchTargetInfo::getGCCRegAliases() const {
  return llvm::makeArrayRef(GCCRegAliases);
}

void FunnyarchTargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  // Define the __FUNNYARCH__ macro when building for this target
  Builder.defineMacro("__FUNNYARCH__");
}
