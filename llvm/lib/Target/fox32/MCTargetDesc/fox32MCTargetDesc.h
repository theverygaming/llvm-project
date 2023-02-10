//===- fox32MCTargetDesc.h - fox32 Target Descriptions --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides fox32 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCTARGETDESC_H
#define LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCTARGETDESC_H

#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;

MCCodeEmitter *createfox32MCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);

MCAsmBackend *createfox32AsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createfox32ELFObjectWriter(uint8_t OSABI,
                                                                 bool Is64Bit);

} // end namespace llvm

// Defines symbolic names for fox32 registers.
#define GET_REGINFO_ENUM
#include "fox32GenRegisterInfo.inc"

// Defines symbolic names for fox32 instructions.
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "fox32GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "fox32GenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCTARGETDESC_H
