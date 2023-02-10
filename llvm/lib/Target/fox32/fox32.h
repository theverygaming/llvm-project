//===-- fox32.h - Top-level interface for fox32 ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// fox32 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32_H
#define LLVM_LIB_TARGET_FOX32_FOX32_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class fox32TargetMachine;
class FunctionPass;

FunctionPass *createfox32ISelDag(fox32TargetMachine &TM);
} // end namespace llvm

#endif // LLVM_LIB_TARGET_FOX32_FOX32_H
