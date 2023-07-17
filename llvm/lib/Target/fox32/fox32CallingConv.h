//===-- fox32CallingConv.h - fox32 Calling Convention-----------------*- C++
//-*-===//
//
// Part of LLVM-fox32, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the fox32 calling convention.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32CALLINGCONV_H
#define LLVM_LIB_TARGET_FOX32_FOX32CALLINGCONV_H

#include "MCTargetDesc/fox32MCTargetDesc.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/Support/MachineValueType.h"

namespace llvm {

/// Regular calling convention.
bool CC_fox32(unsigned ValNo, MVT ValVT, MVT LocVT,
              CCValAssign::LocInfo LocInfo, ISD::ArgFlagsTy ArgFlags,
              CCState &State);

} // namespace llvm

#endif // LLVM_LIB_TARGET_FOX32_FOX32CALLINGCONV_H
