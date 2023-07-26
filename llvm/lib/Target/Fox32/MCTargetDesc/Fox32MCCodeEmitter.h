//===-- Fox32MCCodeEmitter.h - Fox32 Code Emitter ---------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declarations for the code emitter which are useful
/// outside of the emitter itself.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCCODEEMITTER_H
#define LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCCODEEMITTER_H

#include <cstdint>

namespace llvm {
namespace Fox32 {

const uint8_t *getMCInstrBeads(unsigned);

} // namespace Fox32
} // namespace llvm

#endif // LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCCODEEMITTER_H
