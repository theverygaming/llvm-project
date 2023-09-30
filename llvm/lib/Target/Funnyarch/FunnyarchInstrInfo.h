//===-- FunnyarchInstrInfo.h - Funnyarch Instruction Information ----------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Funnyarch implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHINSTRINFO_H
#define LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHINSTRINFO_H

#include "Funnyarch.h"
#include "FunnyarchRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "FunnyarchGenInstrInfo.inc"

namespace llvm {

class FunnyarchInstrInfo : public FunnyarchGenInstrInfo {
public:
  explicit FunnyarchInstrInfo(const FunnyarchSubtarget &STI);

protected:
  const FunnyarchSubtarget &Subtarget;

public:
  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, Register SrcReg,
                           bool IsKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;

  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MI, Register DestReg,
                            int FrameIndex, const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const override;
};
} // namespace llvm

#endif // end LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHINSTRINFO_H
