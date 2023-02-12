//=- fox32BaseInfo.h - Top level definitions for fox32 MC -*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone enum definitions and helper function
// definitions for the fox32 target useful for the compiler back-end and the
// MC libraries.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32BASEINFO_H
#define LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32BASEINFO_H

#include "MCTargetDesc/fox32MCTargetDesc.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/SubtargetFeature.h"

namespace llvm {

namespace fox32ABI {

// Returns the register used to hold the stack pointer after realignment.
MCRegister getBPReg();
} // end namespace fox32ABI

} // end namespace llvm

#endif // LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32BASEINFO_H
