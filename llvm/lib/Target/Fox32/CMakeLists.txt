add_llvm_component_group(Fox32)

set(LLVM_TARGET_DEFINITIONS Fox32.td)

tablegen(LLVM Fox32GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM Fox32GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM Fox32GenCodeEmitter.inc -gen-emitter)
tablegen(LLVM Fox32GenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM Fox32GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM Fox32GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM Fox32GenCallingConv.inc -gen-callingconv)
tablegen(LLVM Fox32GenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM Fox32GenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM Fox32GenDisassemblerTable.inc -gen-disassembler)

# Fox32CommonTableGen must be defined
add_public_tablegen_target(Fox32CommonTableGen)

add_llvm_target(Fox32CodeGen
  Fox32AsmPrinter.cpp
  Fox32FrameLowering.cpp
  Fox32InstrInfo.cpp
  Fox32ISelLowering.cpp
  Fox32RegisterInfo.cpp
  Fox32Subtarget.cpp
  Fox32TargetObjectFile.cpp
  Fox32ISelDAGToDAG.cpp
  Fox32TargetMachine.cpp

  LINK_COMPONENTS
  AsmPrinter
  SelectionDAG
  Target
  
  ADD_TO_COMPONENT
  Fox32
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
# TODO: fix disassembler
#add_subdirectory(Disassembler)
