//=== Fox32.h - Top-level interface for Fox32 representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Fox32 backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32_H
#define LLVM_LIB_TARGET_FOX32_FOX32_H

#include "MCTargetDesc/Fox32MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class FunctionPass;

  // Declare functions to create passes here!

} // end namespace llvm;

#endif // end LLVM_LIB_TARGET_FOX32_FOX32_H
