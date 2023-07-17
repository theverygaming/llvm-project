//=== Fox32.td - Describe the Fox32 Target Machine ---------*- tablegen -*-===//
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

include "Fox32Schedule.td"
include "Fox32RegisterInfo.td"
include "Fox32CallingConv.td"
include "Fox32InstrInfo.td"

def Fox32InstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Fox32 processors supported
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic",  NoSchedModel, []>;

//===----------------------------------------------------------------------===//
// Fox32 Target declaration
//===----------------------------------------------------------------------===//

def Fox32 : Target {
  let InstructionSet = Fox32InstrInfo;
}
