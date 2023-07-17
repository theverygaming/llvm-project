//===-- Fox32TargetMachine.cpp - Define TargetMachine for Fox32 -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Fox32 target spec.
//
//===----------------------------------------------------------------------===//

#include "Fox32TargetMachine.h"
#include "Fox32ISelDAGToDAG.h"
#include "Fox32Subtarget.h"
#include "Fox32TargetObjectFile.h"
#include "TargetInfo/Fox32TargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFox32Target() {
  // Register the target.
  //- Little endian Target Machine
  RegisterTargetMachine<Fox32TargetMachine> X(getTheFox32Target());
}

static std::string computeDataLayout() {
  std::string Ret = "";

  // Little endian
  Ret += "e";

  // ELF name mangling
  Ret += "-m:e";

  // 32-bit pointers, 32-bit aligned
  Ret += "-p:32:32";

  // 64-bit integers, 64 bit aligned
  Ret += "-i64:64";

  // 32-bit native integer width i.e register are 32-bit
  Ret += "-n32";

  // 128-bit natural stack alignment
  Ret += "-S128";

  return Ret;
}

static Reloc::Model getEffectiveRelocModel(Optional<CodeModel::Model> CM,
                                           Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

Fox32TargetMachine::Fox32TargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       Optional<CodeModel::Model> CM,
                                       CodeGenOpt::Level OL,
                                       bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(), TT, CPU, FS, Options,
                        getEffectiveRelocModel(CM, RM),
                        getEffectiveCodeModel(CM, CodeModel::Medium), OL),
      TLOF(std::make_unique<Fox32TargetObjectFile>()) {
  // initAsmInfo will display features by llc -march=fox32 on 3.7
  initAsmInfo();
}

const Fox32Subtarget *
Fox32TargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    I = std::make_unique<Fox32Subtarget>(TargetTriple, CPU, FS, *this);
  }
  return I.get();
}

namespace {
class Fox32PassConfig : public TargetPassConfig {
public:
  Fox32PassConfig(Fox32TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  Fox32TargetMachine &getFox32TargetMachine() const {
    return getTM<Fox32TargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
}

TargetPassConfig *Fox32TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new Fox32PassConfig(*this, PM);
}

// Install an instruction selector pass using
// the ISelDag to gen Fox32 code.
bool Fox32PassConfig::addInstSelector() {
  addPass(new Fox32DAGToDAGISel(getFox32TargetMachine(), getOptLevel()));
  return false;
}

// Implemented by targets that want to run passes immediately before
// machine code is emitted. return true if -print-machineinstrs should
// print out the code after the passes.
void Fox32PassConfig::addPreEmitPass() {
}
