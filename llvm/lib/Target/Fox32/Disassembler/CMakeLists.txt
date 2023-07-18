add_llvm_component_library(LLVMFox32Disassembler
  Fox32Disassembler.cpp

  LINK_COMPONENTS
  Fox32Desc
  Fox32Info
  MCDisassembler
  Support

  ADD_TO_COMPONENT
  Fox32
)
