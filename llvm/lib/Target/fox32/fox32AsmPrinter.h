//===- fox32AsmPrinter.h - fox32 LLVM Assembly Printer -*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// fox32 Assembly printer class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32ASMPRINTER_H
#define LLVM_LIB_TARGET_FOX32_FOX32ASMPRINTER_H

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class LLVM_LIBRARY_VISIBILITY fox32AsmPrinter : public AsmPrinter {
  const MCSubtargetInfo *STI;

public:
  explicit fox32AsmPrinter(TargetMachine &TM,
                           std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), STI(TM.getMCSubtargetInfo()) {}

  StringRef getPassName() const override { return "fox32 Assembly Printer"; }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void emitInstruction(const MachineInstr *MI) override;

  // tblgen'erated function.
  bool emitPseudoExpansionLowering(MCStreamer &OutStreamer,
                                   const MachineInstr *MI);
  // Wrapper needed for tblgenned pseudo lowering.
  bool lowerOperand(const MachineOperand &MO, MCOperand &MCOp) const {
    // TODO
    // return lowerfox32MachineOperandToMCOperand(MO, MCOp, *this);
    return true;
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_FOX32_FOX32ASMPRINTER_H
