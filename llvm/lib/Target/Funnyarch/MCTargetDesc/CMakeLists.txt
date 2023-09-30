add_llvm_component_library(LLVMFunnyarchDesc
  FunnyarchMCAsmInfo.cpp
  FunnyarchMCTargetDesc.cpp
  FunnyarchInstPrinter.cpp
  FunnyarchMCCodeEmitter.cpp
  FunnyarchAsmBackend.cpp
  FunnyarchELFObjectWriter.cpp

  LINK_COMPONENTS
  MC

  ADD_TO_COMPONENT
  Funnyarch
)
