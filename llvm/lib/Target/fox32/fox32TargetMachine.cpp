#include "fox32TargetMachine.h"
#include "TargetInfo/fox32TargetInfo.h"
#include "fox32.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializefox32Target() {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  // Register the target.
  //- Little endian Target Machine
  RegisterTargetMachine<fox32TargetMachine> X(getThefox32Target());
}

static std::string computeDataLayout(const Triple &TT) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  std::string ret = "";
  ret += "e";        // Little endian
  ret += "-m:e";     // ELF name mangling
  ret += "-p:32:32"; // 32-bit pointers, 32-bit aligned
  ret += "-i64:64";  // 64-bit integers, 64 bit aligned
  ret += "-n32";     // 32-bit native integer width i.e register are 32-bit
  ret += "-S8";      // 8-bit natural stack alignment
  return ret;
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
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
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  initAsmInfo();
}

fox32TargetMachine::~fox32TargetMachine() = default;

const fox32Subtarget *
fox32TargetMachine::getSubtargetImpl(const Function &F) const {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
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
    I = std::make_unique<fox32Subtarget>(TargetTriple, CPU, FS, *this);
  }
  printf("RETURN %s:%s:%d\n", __func__, __FILE__, __LINE__);
  return I.get();
}

namespace {
class fox32PassConfig : public TargetPassConfig {
public:
  fox32PassConfig(fox32TargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {
    printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  }

  fox32TargetMachine &getfox32TargetMachine() const {
    printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
    return getTM<fox32TargetMachine>();
  }

  void addIRPasses() override;
  bool addInstSelector() override;
};
} // end namespace

TargetPassConfig *fox32TargetMachine::createPassConfig(PassManagerBase &PM) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  return new fox32PassConfig(*this, PM);
}

void fox32PassConfig::addIRPasses() {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  // addPass(createAtomicExpandPass());

  TargetPassConfig::addIRPasses();
}

bool fox32PassConfig::addInstSelector() {
  addPass(createfox32ISelDag(getfox32TargetMachine()));
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  return false;
}
