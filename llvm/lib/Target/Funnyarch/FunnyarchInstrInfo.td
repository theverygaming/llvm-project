//== FunnyarchInstrInfo.td - Target Description for Funnyarch Target -*- tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Funnyarch implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

// Procedure return
def funnyarch_ret : SDNode<"FunnyarchISD::Ret", SDTNone,
                       [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

// Procedure calling
def SDT_CallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>,
                                       SDTCisVT<1, i32>]>;
def SDT_CallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i32>,
                                    SDTCisVT<1, i32>]>;

// These are target-independent nodes, but have target-specific formats.
def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_CallSeqStart,
                           [SDNPHasChain, SDNPOutGlue]>;
def callseq_end   : SDNode<"ISD::CALLSEQ_END", SDT_CallSeqEnd,
                           [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

//===----------------------------------------------------------------------===//
// Operand and SDNode transformation definitions.
//===----------------------------------------------------------------------===//

class ImmAsmOperand<string prefix, int width, string suffix> : AsmOperandClass {
  let Name = prefix # "Imm" # width # suffix;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

class SImmAsmOperand<int width, string suffix = "">
    : ImmAsmOperand<"S", width, suffix> {
}

class UImmAsmOperand<int width, string suffix = "">
    : ImmAsmOperand<"U", width, suffix> {
}

def UImmLog2WSizeAsmOperand : AsmOperandClass {
  let Name = "UImmLog2WSize";
  let RenderMethod = "addImmOperands";
  let DiagnosticType = "InvalidUImmLog2WSize";
}

def uimmlog2wsize : Operand<i32>, ImmLeaf<i32, [{
  return isUInt<5>(Imm);
}]> {
  let ParserMatchClass = UImmLog2WSizeAsmOperand;
  // TODO: should ensure invalid shamt is rejected when decoding.
  let DecoderMethod = "decodeUImmOperand<5>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (!MCOp.evaluateAsConstantImm(Imm))
      return false;
    return isUInt<5>(Imm);
  }];
  let OperandType = "OPERAND_UIMMLOG2WSIZE";
  let OperandNamespace = "FunnyarchOp";
}

def simm12 : Operand<i32>, ImmLeaf<i32, [{return isInt<12>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<12>;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeSImmOperand<12>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<12>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM12";
  let OperandNamespace = "FunnyarchOp";
}

class UImm20Operand : Operand<i32> {
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeUImmOperand<20>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isUInt<20>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_UIMM20";
  let OperandNamespace = "FunnyarchOp";
}

def uimm32 : Operand<i32>, ImmLeaf<i32, [{return isInt<32>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<32>;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeUImmOperand<32>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isUInt<32>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_UIMM32";
  let OperandNamespace = "FunnyarchOp";
}

def uimm20_lui : UImm20Operand {
  let ParserMatchClass = UImmAsmOperand<20, "LUI">;
}
def uimm20_auipc : UImm20Operand {
  let ParserMatchClass = UImmAsmOperand<20, "AUIPC">;
}

// Standalone (codegen-only) immleaf patterns.
def simm32     : ImmLeaf<i32, [{return isInt<32>(Imm);}]>;
def simm32hi20 : ImmLeaf<i32, [{return isShiftedInt<20, 12>(Imm);}]>;
// A mask value that won't affect significant shift bits.
def immbottomwsizeset : ImmLeaf<i32, [{
  return countTrailingOnes<uint64_t>(Imm) >= 5;
}]>;

// Extract least significant 12 bits from an immediate value and sign extend
// them.
def LO12Sext : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant(SignExtend64<12>(N->getZExtValue()),
                                   SDLoc(N), N->getValueType(0));
}]>;

// Extract the most significant 20 bits from an immediate value. Add 1 if bit
// 11 is 1, to compensate for the low 12 bits in the matching immediate addi
// or ld/st being negative.
def HI20 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant(((N->getZExtValue()+0x800) >> 12) & 0xfffff,
                                   SDLoc(N), N->getValueType(0));
}]>;

//===----------------------------------------------------------------------===//
// Instruction Formats
//===----------------------------------------------------------------------===//

include "FunnyarchInstrFormats.td"

//===----------------------------------------------------------------------===//
// Instruction Class Templates
//===----------------------------------------------------------------------===//

/*def : Pat<(simm12:$imm), (ADDI R0, simm12:$imm)>;
def : Pat<(simm32hi20:$imm), (LUI (HI20 imm:$imm))>;
def : Pat<(simm32:$imm), (ADDI (LUI (HI20 imm:$imm)), (LO12Sext imm:$imm))>;*/

//===----------------------------------------------------------------------===//
// Instructions
//===----------------------------------------------------------------------===//

// funnyarch instructions

def FUMOV_E7 : FUInstE7<0x0, OPC_MOV_E7, CondAlways, "mov", "$rtgt, $rsrc", (outs GPR:$rtgt), (ins GPR:$rsrc), []>;

def FUADD_E1 : FUInstE1<0x0, OPC_ADD_E1, CondAlways, "add", "$rtgt, $rsrc1, $rsrc2", (outs GPR:$rtgt), (ins GPR:$rsrc1, GPR:$rsrc2), []>;

class PatGprGpr<SDPatternOperator OpNode, FUInstE1 Inst>
    : Pat<(OpNode GPR:$rsrc1, GPR:$rsrc2), (Inst GPR:$rsrc1, GPR:$rsrc2)>;

def : PatGprGpr<add, FUADD_E1>;

let isReturn = 1, isBarrier = 1, isTerminator = 1 in
def PseudoRET : Pseudo<(outs), (ins), [(funnyarch_ret)]>, PseudoInstExpansion<(FUMOV_E7 RIP, RLR)>;

let Defs = [R2], Uses = [R2] in {
def ADJCALLSTACKDOWN : Pseudo<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                              [(callseq_start timm:$amt1, timm:$amt2)]>;
def ADJCALLSTACKUP   : Pseudo<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                              [(callseq_end timm:$amt1, timm:$amt2)]>;
} // end Defs = [R2], Uses = [R2]
