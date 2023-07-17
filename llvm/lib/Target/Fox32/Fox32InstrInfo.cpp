//===-- Fox32InstrInfo.cpp - Fox32 Instruction Information ----------------===//
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

#include "Fox32InstrInfo.h"

#include "Fox32TargetMachine.h"
#include "Fox32MachineFunction.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "Fox32GenInstrInfo.inc"

Fox32InstrInfo::Fox32InstrInfo(const Fox32Subtarget &STI)
    : Fox32GenInstrInfo(Fox32::ADJCALLSTACKDOWN, Fox32::ADJCALLSTACKUP),
      Subtarget(STI)
{
}
