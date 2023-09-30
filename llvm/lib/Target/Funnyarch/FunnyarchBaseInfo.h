//===-- FunnyarchBaseInfo.h - Top level definitions for Funnyarch MC ----*- C++
//-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone enum definitions for the Funnyarch target
// useful for the compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHBASEINFO_H
#define LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHBASEINFO_H

#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/SubtargetFeature.h"

namespace llvm {

// FunnyarchII - This namespace holds all of the target specific flags that
// instruction info tracks. All definitions must match FunnyarchInstrFormats.td.
namespace FunnyarchII {
enum {
  InstFormatPseudo = 0,
  InstFormatE1 = 1,
  InstFormatE2 = 2,
  InstFormatE3 = 3,
  InstFormatE4 = 4,
  InstFormatE5 = 5,
  InstFormatE6 = 6,
  InstFormatE7 = 7,

  // FIXME: remove this
  InstFormatR = 1,
  InstFormatI = 3,
  InstFormatU = 6,

  InstFormatMask = 31
};

} // namespace FunnyarchII

namespace FunnyarchOp {
enum OperandType : unsigned {
  OPERAND_FIRST_FUNNYARCH_IMM = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM4 = OPERAND_FIRST_FUNNYARCH_IMM,
  OPERAND_UIMM5,
  OPERAND_UIMM12,
  OPERAND_SIMM12,
  OPERAND_SIMM13_LSB0,
  OPERAND_UIMM20,
  OPERAND_UIMM32,
  OPERAND_SIMM21_LSB0,
  OPERAND_UIMMLOG2WSIZE,
  OPERAND_LAST_FUNNYARCH_IMM = OPERAND_UIMMLOG2WSIZE
};
} // namespace FunnyarchOp

} // namespace llvm

#endif
