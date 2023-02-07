#include "fox32TargetMachine.h"
#include "TargetInfo/fox32TargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializefox32Target() {
  // Register the target.
  //- Little endian Target Machine
  RegisterTargetMachine<fox32TargetMachine> X(getThefox32Target());
}

static std::string computeDataLayout(const Triple &TT) {
  return "e-m:e-p:32:32-i64:64-n32-S128"; // TODO
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

fox32TargetMachine::fox32TargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       Optional<CodeModel::Model> CM,
                                       CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

fox32TargetMachine::~fox32TargetMachine() = default;

namespace {
class fox32PassConfig : public TargetPassConfig {
public:
  fox32PassConfig(fox32TargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  fox32TargetMachine &getfox32TargetMachine() const {
    return getTM<fox32TargetMachine>();
  }

  void addIRPasses() override;
  bool addInstSelector() override;
};
} // end namespace

TargetPassConfig *fox32TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new fox32PassConfig(*this, PM);
}

void fox32PassConfig::addIRPasses() {
  addPass(createAtomicExpandPass());

  TargetPassConfig::addIRPasses();
}

bool fox32PassConfig::addInstSelector() {
  // TODO
  // addPass(createfox32ISelDag(getfox32TargetMachine()));

  return false;
}
