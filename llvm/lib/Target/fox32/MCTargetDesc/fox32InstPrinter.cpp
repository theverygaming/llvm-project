//===- fox32InstPrinter.cpp - Convert fox32 MCInst to asm syntax --===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an fox32 MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "fox32InstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-asm-printer"

#define GET_REGINFO_ENUM
#include "fox32GenRegisterInfo.inc"

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "fox32GenAsmWriter.inc"

void fox32InstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                 StringRef Annot, const MCSubtargetInfo &STI,
                                 raw_ostream &O) {
  if (!printAliasInstr(MI, Address, STI, O))
    printInstruction(MI, Address, STI, O);
  printAnnotation(O, Annot);
}

void fox32InstPrinter::printRegName(raw_ostream &O, unsigned RegNo) const {
  O << '$' << getRegisterName(RegNo);
}

void fox32InstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                    const MCSubtargetInfo &STI,
                                    raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(OpNo);

  if (MO.isReg()) {
    printRegName(O, MO.getReg());
    return;
  }

  if (MO.isImm()) {
    O << MO.getImm();
    return;
  }

  assert(MO.isExpr() && "Unknown operand kind in printOperand");
  MO.getExpr()->print(O, &MAI);
}

const char *fox32InstPrinter::getRegisterName(unsigned RegNo) {
  // Default print reg alias name
  return getRegisterName(RegNo, fox32::RegAliasName);
}
