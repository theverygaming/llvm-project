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

static bool getFox32InstrOpCount(uint8_t opcode, unsigned int *count) {
  switch (opcode) {
  case 0x00:
    *count = 0;
    return true;
  case 0x01:
  case 0x02:
  case 0x03:
  case 0x04:
  case 0x05:
  case 0x06:
  case 0x07:
    *count = 2;
    return true;
  case 0x08:
  case 0x09:
  case 0x0A:
    *count = 1;
    return true;
  case 0x0B:
    *count = 2;
    return true;
  case 0x0C:
  case 0x0D:
  case 0x10:
    *count = 0;
    return true;
  case 0x11:
    *count = 1;
    return true;
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
    *count = 2;
    return true;
  case 0x18:
  case 0x19:
  case 0x1A:
    *count = 1;
    return true;
  case 0x1B:
    *count = 2;
    return true;
  case 0x1C:
  case 0x1D:
  case 0x20:
    *count = 0;
    return true;
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
    *count = 2;
    return true;
  case 0x28:
  case 0x29:
    *count = 1;
    return true;
  case 0x2A:
    *count = 0;
    return true;
  case 0x2C:
  case 0x2D:
  case 0x31:
    *count = 1;
    return true;
  case 0x32:
    *count = 2;
    return true;
  case 0x33:
    *count = 1;
    return true;
  case 0x34:
  case 0x35:
  case 0x39:
    *count = 2;
    return true;
  case 0x3A:
    *count = 0;
    return true;
  case 0x3D:
    *count = 1;
    return true;
  default:
    *count = 0;
    return false;
  }
}

static unsigned int getFox32OpFieldSize(uint8_t type, uint8_t opSize) {
  uint8_t opsizes[] = {1, 2, 3, 0};
  switch (type) {
  case 0: // register
  case 1: // register pointer
    return 1;
  case 2: // immediate
    return opsizes[opSize];
  case 3: // immediate pointer
    return 4;
  }
  return 0;
}

static bool getFox32InstrSize(uint16_t control, unsigned int *size) {
  uint8_t srcType = (control >> 0) & 0x3;
  uint8_t dstType = (control >> 2) & 0x3;
  uint8_t opcode = (control >> 8) & 0x3F;
  uint8_t opSize = (control >> 14) & 0x3;

  if (opSize > 2) { // reserved opsize
    return false;
  }

  unsigned int opcount;
  if (!getFox32InstrOpCount(opcode, &opcount)) {
    return false;
  }

  *size = 2; // control word

  if (opcount >= 1) {
    *size += getFox32OpFieldSize(srcType, opSize);
  }
  if (opcount == 2) {
    *size += getFox32OpFieldSize(dstType, opSize);
  }

  return true;
}

DecodeStatus Fox32Disassembler::getInstruction(MCInst &Instr, uint64_t &Size,
                                               ArrayRef<uint8_t> Bytes,
                                               uint64_t Address,
                                               raw_ostream &CStream) const {
  DecodeStatus Result;
  std::vector<uint64_t> instarr;
  instarr.push_back((uint64_t)Bytes.data()[0] |
                    ((uint64_t)Bytes.data()[1] << 8));
  // APInt Insn(16, support::endian::read16le(Bytes.data()));
  APInt Insn(64, ArrayRef<uint64_t>(instarr));
  // 2 bytes of data are consumed, so set Size to 2
  // If we don't do this, disassembler may generate result even
  // the encoding is invalid. We need to let it fail correctly.
  Size = 2;

  unsigned int instrSize;
  if (!getFox32InstrSize(*Insn.getRawData(), &instrSize)) {
    printf("instr decode failure (getFox32InstrSize)\n");
    return DecodeStatus::Fail;
  }
  printf("instrsize: %u i: %p\n", instrSize, *Insn.getRawData());
  Size = instrSize;
  // read remaining bytes
  uint64_t instarr_pos = 16;
  for (uint64_t i = 0; i < (Size - 2); i++) {
    if (instarr_pos % 64 == 0 && instarr_pos != 0) {
      instarr.push_back(0);
    }
    instarr.back() |= ((uint64_t)Bytes.data()[2 + i]) << (instarr_pos % 64);
    instarr_pos += 8;
  }
  Insn = APInt(Size * 8, ArrayRef<uint64_t>(instarr));
  printf("instrsize: %u i: %p d: %d\n", instrSize, *Insn.getRawData(),
         Insn.getBitWidth());

  const uint8_t *DecoderTable = nullptr;
  switch (Insn.getBitWidth()) {
  case 16:
    DecoderTable = DecoderTable16;
    break;
  case 24:
    DecoderTable = DecoderTable24;
    break;
  case 80:
    DecoderTable = DecoderTable80;
    break;
  default:
    return DecodeStatus::Fail;
  }
  Result = decodeInstruction(DecoderTable, Instr, Insn, Address, this, STI);

  if (Result == DecodeStatus::Success) {
    printf("instr decode OK\n");
  } else {
    printf("instr decode failure\n");
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
