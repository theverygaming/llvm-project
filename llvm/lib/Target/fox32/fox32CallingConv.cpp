
//===-- fox32CallingConv.cpp - fox32 Calling Convention -------------------===//
//
// Part of LLVM-fox32, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the fox32 calling convention.
//
//===----------------------------------------------------------------------===//

#include "fox32CallingConv.h"

#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/IR/DataLayout.h"

#include "fox32GenCallingConv.inc"
