add_llvm_component_group(fox32)

set(LLVM_TARGET_DEFINITIONS fox32.td)

add_llvm_target(fox32CodeGen
  fox32TargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  fox32
  )

add_subdirectory(TargetInfo)
