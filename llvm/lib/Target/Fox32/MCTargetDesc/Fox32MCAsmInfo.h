//===-- Fox32MCAsmInfo.h - Fox32 Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the Fox32MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCASMINFO_H
#define LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class Fox32MCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit Fox32MCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_FOX32_MCTARGETDESC_FOX32MCASMINFO_H
