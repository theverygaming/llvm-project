//=- fox32TargetMachine.h - Define TargetMachine for fox32 -*- C++ -*-//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the fox32 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32TARGETMACHINE_H
#define LLVM_LIB_TARGET_FOX32_FOX32TARGETMACHINE_H

#include "fox32Subtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class fox32TargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  mutable StringMap<std::unique_ptr<fox32Subtarget>> SubtargetMap;

public:
  fox32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                     CodeGenOpt::Level OL, bool JIT);
  ~fox32TargetMachine() override;

  const fox32Subtarget *getSubtargetImpl(const Function &F) const override;
  const fox32Subtarget *getSubtargetImpl() const = delete;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
    return TLOF.get();
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_FOX32_FOX32TARGETMACHINE_H
