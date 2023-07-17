//=- fox32CallingConv.td - Calling Conventions fox32 -*- tablegen -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This describes the calling conventions for the fox32 architecture.
//
//===----------------------------------------------------------------------===//

def fox32_CalleeSavedRegs : CalleeSavedRegs<(add X8, X9)>;

let Entry = 1 in {
def CC_fox32 : CallingConv<[
  CCIfPtr<CCAssignToReg<[X0, X1, X2, X3, X4, X5, X6, X7]>>,

  CCIfType<[i32], CCAssignToReg<[X0, X1, X2, X3, X4, X5, X6, X7]>>,

  // Values that wouldn't fit anywhere else are passed directly on the stack.
  CCAssignToStack<0, 1>,
]>;
}
