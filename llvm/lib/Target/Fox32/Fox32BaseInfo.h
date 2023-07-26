//===-- Fox32BaseInfo.h - Top level definitions for Fox32 MC ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone enum definitions for the Fox32 target
// useful for the compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32BASEINFO_H
#define LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32BASEINFO_H

#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/SubtargetFeature.h"

namespace llvm {

// Fox32II - This namespace holds all of the target specific flags that
// instruction info tracks. All definitions must match Fox32InstrFormats.td.
namespace Fox32II {
enum {
  InstFormatPseudo = 0,
  InstFormatR = 1,
  InstFormatI = 3,
  InstFormatU = 6,

  InstFormatMask = 31
};

} // namespace Fox32II

namespace Fox32Op {
enum OperandType : unsigned {
  OPERAND_FIRST_FOX32_IMM = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM4 = OPERAND_FIRST_FOX32_IMM,
  OPERAND_UIMM5,
  OPERAND_UIMM12,
  OPERAND_SIMM12,
  OPERAND_SIMM13_LSB0,
  OPERAND_UIMM20,
  OPERAND_UIMM32,
  OPERAND_SIMM21_LSB0,
  OPERAND_UIMMLOG2WSIZE,
  OPERAND_LAST_FOX32_IMM = OPERAND_UIMMLOG2WSIZE
};
} // namespace Fox32Op

} // namespace llvm

#endif
