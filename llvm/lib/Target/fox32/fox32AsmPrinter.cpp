//===- fox32AsmPrinter.cpp - fox32 LLVM Assembly Printer -*- C++ -*--=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to GAS-format fox32 assembly language.
//
//===----------------------------------------------------------------------===//

#include "fox32AsmPrinter.h"
#include "TargetInfo/fox32TargetInfo.h"
#include "fox32.h"
#include "fox32TargetMachine.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-asm-printer"

void fox32AsmPrinter::emitInstruction(const MachineInstr *MI) {
  // TODO
  // fox32_MC::verifyInstructionPredicates(MI->getOpcode(),
  // getSubtargetInfo().getFeatureBits());

  // Do any auto-generated pseudo lowerings.
  if (emitPseudoExpansionLowering(*OutStreamer, MI))
    return;

  MCInst TmpInst;

  /*if (!lowerfox32MachineInstrToMCInst(MI, TmpInst, *this)) {
    EmitToStreamer(*OutStreamer, TmpInst);
  }*/
}

bool fox32AsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  AsmPrinter::runOnMachineFunction(MF);
  return true;
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializefox32AsmPrinter() {
  RegisterAsmPrinter<fox32AsmPrinter> X(getThefox32Target());
}

// TODO: supposed to be tablegenned
bool fox32AsmPrinter::emitPseudoExpansionLowering(MCStreamer &OutStreamer,
                                                  const MachineInstr *MI) {
  return true;
}
