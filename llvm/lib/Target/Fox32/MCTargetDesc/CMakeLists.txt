add_llvm_component_library(LLVMFox32Desc
  Fox32MCAsmInfo.cpp
  Fox32MCTargetDesc.cpp
  Fox32InstPrinter.cpp
  Fox32MCCodeEmitter.cpp
  Fox32AsmBackend.cpp
  Fox32ELFObjectWriter.cpp

  LINK_COMPONENTS
  MC

  ADD_TO_COMPONENT
  Fox32
)
