//===-- Fox32Disassembler.cpp - Disassembler for Fox32 ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is part of the Fox32 Disassembler.
//
//===----------------------------------------------------------------------===//

#include "Fox32.h"
#include "Fox32RegisterInfo.h"
#include "Fox32Subtarget.h"
#include "MCTargetDesc/Fox32MCTargetDesc.h"
#include "TargetInfo/Fox32TargetInfo.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDecoderOps.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

static const unsigned RegisterDecoderTable[] = {
    Fox32::R0,  Fox32::R1,  Fox32::R2,  Fox32::R3,   Fox32::R4,  Fox32::R5,
    Fox32::R6,  Fox32::R7,  Fox32::R8,  Fox32::R9,   Fox32::R10, Fox32::R11,
    Fox32::R12, Fox32::R13, Fox32::R14, Fox32::R15,  Fox32::R16, Fox32::R17,
    Fox32::R18, Fox32::R19, Fox32::R20, Fox32::R21,  Fox32::R22, Fox32::R23,
    Fox32::R24, Fox32::R25, Fox32::R26, Fox32::R27,  Fox32::R28, Fox32::R29,
    Fox32::R30, Fox32::R31, Fox32::RSP, Fox32::RESP, Fox32::RFP};

static DecodeStatus DecodeGPRRegisterClass(MCInst &Inst, uint32_t RegNo,
                                           uint64_t Address,
                                           const MCDisassembler *Decoder) {
  if (RegNo > 34) {
    return MCDisassembler::Fail;
  }

  unsigned Register = RegisterDecoderTable[RegNo];
  Inst.addOperand(MCOperand::createReg(Register));
  return MCDisassembler::Success;
}

template <unsigned N>
static DecodeStatus decodeSImmOperand(MCInst &Inst, uint64_t Imm,
                                      int64_t Address,
                                      const MCDisassembler *Decoder) {
  llvm_unreachable("unimplemented");
}

template <unsigned N>
static DecodeStatus decodeUImmOperand(MCInst &Inst, uint64_t Imm,
                                      int64_t Address,
                                      const MCDisassembler *Decoder) {
  llvm_unreachable("unimplemented");
}

#include "Fox32GenDisassemblerTable.inc"

/// A disassembler class for Fox32.
struct Fox32Disassembler : public MCDisassembler {
  Fox32Disassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}
  virtual ~Fox32Disassembler() {}

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &CStream) const override;
};

DecodeStatus Fox32Disassembler::getInstruction(MCInst &Instr, uint64_t &Size,
                                               ArrayRef<uint8_t> Bytes,
                                               uint64_t Address,
                                               raw_ostream &CStream) const {
  DecodeStatus Result;
  APInt Insn(16, support::endian::read16be(Bytes.data()));
  // 2 bytes of data are consumed, so set Size to 2
  // If we don't do this, disassembler may generate result even
  // the encoding is invalid. We need to let it fail correctly.
  Size = 2;
  Result = decodeInstruction(DecoderTable32, Instr, Insn, Address, this, STI);
  if (Result == DecodeStatus::Success) {
  }
  // Size = InstrLenTable[Instr.getOpcode()] >> 3;
  return Result;
}

static MCDisassembler *createFox32Disassembler(const Target &T,
                                               const MCSubtargetInfo &STI,
                                               MCContext &Ctx) {
  return new Fox32Disassembler(STI, Ctx);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFox32Disassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheFox32Target(),
                                         createFox32Disassembler);
}
