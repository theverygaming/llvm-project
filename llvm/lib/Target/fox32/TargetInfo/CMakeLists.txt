add_llvm_component_library(LLVMfox32Info
  fox32TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  fox32
  )
