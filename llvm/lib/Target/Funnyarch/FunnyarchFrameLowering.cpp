//===-- FunnyarchFrameLowering.cpp - Funnyarch Frame Information
//------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the FunnyarchTargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "FunnyarchFrameLowering.h"
#include "FunnyarchSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

// hasFP - Return true if the specified function should have a dedicated frame
// pointer register.  This is true if the function has variable sized allocas,
// if it needs dynamic stack realignment, if frame pointer elimination is
// disabled, or if the frame address is taken.
bool FunnyarchFrameLowering::hasFP(const MachineFunction &MF) const {
  return false;
}

MachineBasicBlock::iterator
FunnyarchFrameLowering::eliminateCallFramePseudoInstr(
    MachineFunction &MF, MachineBasicBlock &MBB,
    MachineBasicBlock::iterator I) const {
  return MBB.erase(I);
}

void FunnyarchFrameLowering::emitPrologue(MachineFunction &MF,
                                          MachineBasicBlock &MBB) const {
  printf("emitPrologue\n");
}

void FunnyarchFrameLowering::emitEpilogue(MachineFunction &MF,
                                          MachineBasicBlock &MBB) const {
  printf("emitEpilogue\n");
}

bool FunnyarchFrameLowering::hasReservedCallFrame(
    const MachineFunction &MF) const {
  return true;
}

// This method is called immediately before PrologEpilogInserter scans the
// physical registers used to determine what callee saved registers should be
// spilled. This method is optional.
void FunnyarchFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                                  BitVector &SavedRegs,
                                                  RegScavenger *RS) const {
  printf("determineCalleeSaves\n");
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
}
