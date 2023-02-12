add_llvm_component_group(fox32)

set(LLVM_TARGET_DEFINITIONS fox32.td)

tablegen(LLVM fox32GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM fox32GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM fox32GenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM fox32GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM fox32GenDAGISel.inc -gen-dag-isel)

add_public_tablegen_target(fox32CommonTableGen)

add_llvm_target(fox32CodeGen
  fox32TargetMachine.cpp
  fox32AsmPrinter.cpp
  fox32ISelDAGToDAG.cpp
  fox32ISelLowering.cpp
  fox32Subtarget.cpp
  fox32RegisterInfo.cpp
  fox32FrameLowering.cpp
  fox32InstrInfo.cpp

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
