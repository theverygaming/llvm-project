//===-- FunnyarchInstrInfo.cpp - Funnyarch Instruction Information
//----------------===//
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

#include "FunnyarchInstrInfo.h"

#include "FunnyarchInstrBuilder.h"
#include "FunnyarchMachineFunction.h"
#include "FunnyarchTargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "funnyarch-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "FunnyarchGenInstrInfo.inc"

FunnyarchInstrInfo::FunnyarchInstrInfo(const FunnyarchSubtarget &STI)
    : FunnyarchGenInstrInfo(Funnyarch::ADJCALLSTACKDOWN,
                            Funnyarch::ADJCALLSTACKUP),
      Subtarget(STI) {}

static unsigned getLoadStoreRegOpcode(unsigned Reg,
                                      const TargetRegisterClass *RC,
                                      const TargetRegisterInfo *TRI,
                                      const FunnyarchSubtarget &STI,
                                      bool load) {
  printf("getLoadStoreRegOpcode\n");
  return Funnyarch::FUMOV_E7; // FIXME: this is so wrong
  /*switch (TRI->getRegSizeInBits(*RC)) {
  default:
    llvm_unreachable("Unknown spill size");
  case 8:
    if (M68k::DR8RegClass.hasSubClassEq(RC))
      return load ? M68k::MOVM8mp_P : M68k::MOVM8pm_P;
    if (M68k::CCRCRegClass.hasSubClassEq(RC))
      return load ? M68k::MOV16cp : M68k::MOV16pc;

    llvm_unreachable("Unknown 1-byte regclass");
  case 16:
    assert(M68k::XR16RegClass.hasSubClassEq(RC) && "Unknown 2-byte regclass");
    return load ? M68k::MOVM16mp_P : M68k::MOVM16pm_P;
  case 32:
    assert(M68k::XR32RegClass.hasSubClassEq(RC) && "Unknown 4-byte regclass");
    return load ? M68k::MOVM32mp_P : M68k::MOVM32pm_P;
  }*/
}

void FunnyarchInstrInfo::storeRegToStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register SrcReg,
    bool IsKill, int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI) const {
  printf("storeRegToStackSlot\n");
  return; // FIXME: breaks stuff
  const MachineFunction &MF = *MBB.getParent();
  assert(MF.getFrameInfo().getObjectSize(FrameIndex) == 4 &&
         "Stack slot too small for store");
  unsigned Opc = getLoadStoreRegOpcode(SrcReg, RC, TRI, Subtarget, false);
  DebugLoc DL = MBB.findDebugLoc(MI);
  // (0,FrameIndex) <- $reg
  Funnyarch::addFrameReference(BuildMI(MBB, MI, DL, get(Opc)), FrameIndex)
      .addReg(SrcReg, getKillRegState(IsKill));
}

void FunnyarchInstrInfo::loadRegFromStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register DstReg,
    int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI) const {
  printf("loadRegFromStackSlot\n");
  return; // FIXME: breaks stuff
  const MachineFunction &MF = *MBB.getParent();
  assert(MF.getFrameInfo().getObjectSize(FrameIndex) == 4 &&
         "Stack slot too small for store");
  unsigned Opc = getLoadStoreRegOpcode(DstReg, RC, TRI, Subtarget, true);
  DebugLoc DL = MBB.findDebugLoc(MI);
  Funnyarch::addFrameReference(BuildMI(MBB, MI, DL, get(Opc), DstReg),
                               FrameIndex);
}
