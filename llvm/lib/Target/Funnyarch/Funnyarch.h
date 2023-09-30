//=== Funnyarch.h - Top-level interface for Funnyarch representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Funnyarch backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCH_H
#define LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCH_H

#include "MCTargetDesc/FunnyarchMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class FunctionPass;

  // Declare functions to create passes here!

} // end namespace llvm;

#endif // end LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCH_H
