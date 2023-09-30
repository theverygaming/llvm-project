add_llvm_component_library(LLVMFunnyarchDisassembler
  FunnyarchDisassembler.cpp

  LINK_COMPONENTS
  FunnyarchDesc
  FunnyarchInfo
  MCDisassembler
  Support

  ADD_TO_COMPONENT
  Funnyarch
)
