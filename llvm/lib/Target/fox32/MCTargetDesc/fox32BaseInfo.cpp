//= fox32BaseInfo.cpp - Top level definitions for fox32 MC -*- C++ -*-//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements helper functions for the fox32 target useful for the
// compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//

#include "fox32BaseInfo.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

namespace fox32ABI {

// FIXME: other register?
MCRegister getBPReg() { return fox32::X31; }

} // end namespace fox32ABI

} // end namespace llvm
