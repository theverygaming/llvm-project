//===-- FunnyarchDisassembler.cpp - Disassembler for Funnyarch ----------*- C++
//-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is part of the Funnyarch Disassembler.
//
//===----------------------------------------------------------------------===//

#include "Funnyarch.h"
#include "FunnyarchRegisterInfo.h"
#include "FunnyarchSubtarget.h"
#include "MCTargetDesc/FunnyarchMCTargetDesc.h"
#include "TargetInfo/FunnyarchTargetInfo.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDecoderOps.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "funnyarch-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

static const unsigned RegisterDecoderTable[] = {
    Funnyarch::R0,  Funnyarch::R1,  Funnyarch::R2,  Funnyarch::R3,
    Funnyarch::R4,  Funnyarch::R5,  Funnyarch::R6,  Funnyarch::R7,
    Funnyarch::R8,  Funnyarch::R9,  Funnyarch::R10, Funnyarch::R11,
    Funnyarch::R12, Funnyarch::R13, Funnyarch::R14, Funnyarch::R15,
    Funnyarch::R16, Funnyarch::R17, Funnyarch::R18, Funnyarch::R19,
    Funnyarch::R20, Funnyarch::R21, Funnyarch::R22, Funnyarch::R23,
    Funnyarch::R24, Funnyarch::R25, Funnyarch::RFP, Funnyarch::RIPTR,
    Funnyarch::RLR, Funnyarch::RSP, Funnyarch::RIP, Funnyarch::RF};

static DecodeStatus DecodeGPRRegisterClass(MCInst &Inst, uint32_t RegNo,
                                           uint64_t Address,
                                           const MCDisassembler *Decoder) {
  if (RegNo > 31) {
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
  assert(isUInt<N>(Imm) && "Invalid immediate");
  Inst.addOperand(MCOperand::createImm(SignExtend32<N>(Imm)));
  return MCDisassembler::Success;
}

template <unsigned N>
static DecodeStatus decodeUImmOperand(MCInst &Inst, uint64_t Imm,
                                      int64_t Address,
                                      const MCDisassembler *Decoder) {
  assert(isUInt<N>(Imm) && "Invalid immediate");
  Inst.addOperand(MCOperand::createImm(Imm));
  return MCDisassembler::Success;
}

#include "FunnyarchGenDisassemblerTable.inc"

/// A disassembler class for Funnyarch.
struct FunnyarchDisassembler : public MCDisassembler {
  FunnyarchDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}
  virtual ~FunnyarchDisassembler() {}

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &CStream) const override;
};

DecodeStatus FunnyarchDisassembler::getInstruction(MCInst &Instr,
                                                   uint64_t &Size,
                                                   ArrayRef<uint8_t> Bytes,
                                                   uint64_t Address,
                                                   raw_ostream &CStream) const {
  DecodeStatus Result;
  std::vector<uint64_t> instarr;
  instarr.push_back(
      (uint64_t)Bytes.data()[0] | ((uint64_t)Bytes.data()[1] << 8) |
      ((uint64_t)Bytes.data()[2] << 16) | ((uint64_t)Bytes.data()[3] << 24));
  APInt Insn(64, ArrayRef<uint64_t>(instarr));
  Size = 4;

  Result = decodeInstruction(DecoderTable32, Instr, Insn, Address, this, STI);

  if (Result == DecodeStatus::Success) {
    printf("instr decode OK\n");
  } else {
    printf("instr decode failure\n");
  }
  // Size = InstrLenTable[Instr.getOpcode()] >> 3;
  return Result;
}

static MCDisassembler *createFunnyarchDisassembler(const Target &T,
                                                   const MCSubtargetInfo &STI,
                                                   MCContext &Ctx) {
  return new FunnyarchDisassembler(STI, Ctx);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFunnyarchDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheFunnyarchTarget(),
                                         createFunnyarchDisassembler);
}
