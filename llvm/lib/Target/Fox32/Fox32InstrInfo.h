//===-- Fox32InstrInfo.h - Fox32 Instruction Information ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Fox32 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32INSTRINFO_H
#define LLVM_LIB_TARGET_FOX32_FOX32INSTRINFO_H

#include "Fox32.h"
#include "Fox32RegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "Fox32GenInstrInfo.inc"

namespace llvm {

class Fox32InstrInfo : public Fox32GenInstrInfo {
public:
  explicit Fox32InstrInfo(const Fox32Subtarget &STI);

protected:
  const Fox32Subtarget &Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_FOX32_FOX32INSTRINFO_H
