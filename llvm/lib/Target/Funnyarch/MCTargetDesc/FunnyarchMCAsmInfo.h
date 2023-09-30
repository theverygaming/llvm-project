//===-- FunnyarchMCAsmInfo.h - Funnyarch Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the FunnyarchMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHMCASMINFO_H
#define LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class FunnyarchMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit FunnyarchMCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_FUNNYARCH_MCTARGETDESC_FUNNYARCHMCASMINFO_H
