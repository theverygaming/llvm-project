//=== FunnyarchCallingConv.td - Calling Conventions for Funnyarch --*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for Funnyarch architecture.
//===----------------------------------------------------------------------===//

// funnyarch calling convention:
// caller saves r0-r7
// callee saves: r8-r31
// args passed in: r0-r7 and then on stack
// return value in r0

def Funnyarch_CCallingConv : CallingConv<[
  // Handles byval parameters. Tell LLVM what the size and alignment
  // requirements of each stack slot are
  CCIfByVal<CCPassByVal<4, 4>>,

  // Promote i8/i16 to i32
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  // The first 8 arguments are passed in R0-R7
  CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3, R4, R5, R6, R7]>>,

  // Integer values get stored in stack slots that are 4 bytes in size and
  // 4-byte aligned
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

// C Return Convention
def Funnyarch_CRetConv : CallingConv<[
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  // i32 are returned in register R0
  CCIfType<[i32], CCAssignToReg<[R0]>>,

  // Integer values get stored in stack slots that are 4 bytes in size and
  // 4-byte aligned
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def Funnyarch_CalleeSavedRegs : CalleeSavedRegs<(add R0, R1, R2, R3, R4, R5, R6, R7)>;
