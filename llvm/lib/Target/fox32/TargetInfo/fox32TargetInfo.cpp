#include "fox32TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getThefox32Target() {
  static Target Thefox32Target;
  return Thefox32Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializefox32TargetInfo() {
  RegisterTarget<Triple::fox32, /*HasJIT=*/false> X(getThefox32Target(),
                                                    "fox32", "fox32", "fox32");
}
