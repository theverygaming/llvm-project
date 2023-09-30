//=== Funnyarch.td - Describe the Funnyarch Target Machine ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Top tablegen file that pulls in code from the LLVM framework along with
// code specific to this target.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions, Register information, etc
//===----------------------------------------------------------------------===//

include "FunnyarchSchedule.td"
include "FunnyarchRegisterInfo.td"
include "FunnyarchCallingConv.td"
include "FunnyarchInstrInfo.td"

def FunnyarchInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Funnyarch processors supported
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic",  NoSchedModel, []>;

//===----------------------------------------------------------------------===//
// Funnyarch Target declaration
//===----------------------------------------------------------------------===//

def Funnyarch : Target {
  let InstructionSet = FunnyarchInstrInfo;
}
