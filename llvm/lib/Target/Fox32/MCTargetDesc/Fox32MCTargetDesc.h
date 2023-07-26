//===-- Fox32MCTargetDesc.h - Fox32 Target Descriptions ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Fox32 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCTARGETDESC_H
#define LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCTARGETDESC_H

#include "Fox32BaseInfo.h"
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

MCAsmBackend *createFox32AsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);

MCCodeEmitter *createFox32MCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);

std::unique_ptr<MCObjectTargetWriter> createFox32ELFObjectWriter(uint8_t OSABI);
} // namespace llvm

// Defines symbolic names for Fox32 registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "Fox32GenRegisterInfo.inc"

// Defines symbolic names for the Fox32 instructions.
#define GET_INSTRINFO_ENUM
#include "Fox32GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "Fox32GenSubtargetInfo.inc"

#endif // end LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCTARGETDESC_H
