add_llvm_component_group(Funnyarch)

set(LLVM_TARGET_DEFINITIONS Funnyarch.td)

tablegen(LLVM FunnyarchGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM FunnyarchGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM FunnyarchGenCodeEmitter.inc -gen-emitter)
tablegen(LLVM FunnyarchGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM FunnyarchGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM FunnyarchGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM FunnyarchGenCallingConv.inc -gen-callingconv)
tablegen(LLVM FunnyarchGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM FunnyarchGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM FunnyarchGenDisassemblerTable.inc -gen-disassembler)

# FunnyarchCommonTableGen must be defined
add_public_tablegen_target(FunnyarchCommonTableGen)

add_llvm_target(FunnyarchCodeGen
  FunnyarchAsmPrinter.cpp
  FunnyarchFrameLowering.cpp
  FunnyarchInstrInfo.cpp
  FunnyarchISelLowering.cpp
  FunnyarchRegisterInfo.cpp
  FunnyarchSubtarget.cpp
  FunnyarchTargetObjectFile.cpp
  FunnyarchISelDAGToDAG.cpp
  FunnyarchTargetMachine.cpp

  LINK_COMPONENTS
  AsmPrinter
  SelectionDAG
  Target
  
  ADD_TO_COMPONENT
  Funnyarch
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
# TODO: fix disassembler
add_subdirectory(Disassembler)
