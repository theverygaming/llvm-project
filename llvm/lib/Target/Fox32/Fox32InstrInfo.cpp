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

#include "Fox32InstrBuilder.h"
#include "Fox32MachineFunction.h"
#include "Fox32TargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "Fox32GenInstrInfo.inc"

Fox32InstrInfo::Fox32InstrInfo(const Fox32Subtarget &STI)
    : Fox32GenInstrInfo(Fox32::ADJCALLSTACKDOWN, Fox32::ADJCALLSTACKUP),
      Subtarget(STI) {}

static unsigned getLoadStoreRegOpcode(unsigned Reg,
                                      const TargetRegisterClass *RC,
                                      const TargetRegisterInfo *TRI,
                                      const Fox32Subtarget &STI, bool load) {
  return Fox32::ADDI;
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

void Fox32InstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator MI,
                                         Register SrcReg, bool IsKill,
                                         int FrameIndex,
                                         const TargetRegisterClass *RC,
                                         const TargetRegisterInfo *TRI) const {
  const MachineFunction &MF = *MBB.getParent();
  assert(MF.getFrameInfo().getObjectSize(FrameIndex) == 4 &&
         "Stack slot too small for store");
  unsigned Opc = getLoadStoreRegOpcode(SrcReg, RC, TRI, Subtarget, false);
  DebugLoc DL = MBB.findDebugLoc(MI);
  // (0,FrameIndex) <- $reg
  Fox32::addFrameReference(BuildMI(MBB, MI, DL, get(Opc)), FrameIndex)
      .addReg(SrcReg, getKillRegState(IsKill));
}

void Fox32InstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                          MachineBasicBlock::iterator MI,
                                          Register DstReg, int FrameIndex,
                                          const TargetRegisterClass *RC,
                                          const TargetRegisterInfo *TRI) const {
  const MachineFunction &MF = *MBB.getParent();
  assert(MF.getFrameInfo().getObjectSize(FrameIndex) == 4 &&
         "Stack slot too small for store");
  unsigned Opc = getLoadStoreRegOpcode(DstReg, RC, TRI, Subtarget, true);
  DebugLoc DL = MBB.findDebugLoc(MI);
  Fox32::addFrameReference(BuildMI(MBB, MI, DL, get(Opc), DstReg), FrameIndex);
}
