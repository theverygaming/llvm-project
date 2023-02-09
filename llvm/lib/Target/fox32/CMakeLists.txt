add_llvm_component_group(fox32)

set(LLVM_TARGET_DEFINITIONS fox32.td)

tablegen(LLVM fox32GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM fox32GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM fox32GenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM fox32GenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(fox32CommonTableGen)

add_llvm_target(fox32CodeGen
  fox32TargetMachine.cpp
  fox32AsmPrinter.cpp

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

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
