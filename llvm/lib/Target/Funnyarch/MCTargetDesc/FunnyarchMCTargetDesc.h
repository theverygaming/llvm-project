//===-- FunnyarchMCTargetDesc.h - Funnyarch Target Descriptions ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Funnyarch specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHMCTARGETDESC_H
#define LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHMCTARGETDESC_H

#include "FunnyarchBaseInfo.h"
#include "llvm/MC/MCObjectWriter.h"

namespace llvm {
class MCCodeEmitter;
class MCInstrInfo;
class MCContext;

class MCAsmBackend;
class Target;
class MCSubtargetInfo;
class MCRegisterInfo;
class MCTargetOptions;

MCAsmBackend *createFunnyarchAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);

MCCodeEmitter *createFunnyarchMCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);

std::unique_ptr<MCObjectTargetWriter> createFunnyarchELFObjectWriter(uint8_t OSABI);
} // namespace llvm

// Defines symbolic names for Funnyarch registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "FunnyarchGenRegisterInfo.inc"

// Defines symbolic names for the Funnyarch instructions.
#define GET_INSTRINFO_ENUM
#include "FunnyarchGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "FunnyarchGenSubtargetInfo.inc"

#endif // end LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHMCTARGETDESC_H
