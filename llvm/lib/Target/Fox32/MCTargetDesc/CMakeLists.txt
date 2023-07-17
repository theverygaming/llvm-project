add_llvm_component_library(LLVMFox32Desc
  Fox32MCAsmInfo.cpp
  Fox32MCTargetDesc.cpp
  Fox32InstPrinter.cpp

  LINK_COMPONENTS
  MC

  ADD_TO_COMPONENT
  Fox32
)
