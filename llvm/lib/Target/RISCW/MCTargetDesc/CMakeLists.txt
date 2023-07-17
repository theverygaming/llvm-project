add_llvm_component_library(LLVMRISCWDesc
  RISCWMCAsmInfo.cpp
  RISCWMCTargetDesc.cpp
  RISCWInstPrinter.cpp

  LINK_COMPONENTS
  MC

  ADD_TO_COMPONENT
  RISCW
)
