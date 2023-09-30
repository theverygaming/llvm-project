//=== FunnyarchInstrFormats.td - Funnyarch Instruction Formats -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//
//  These instruction format definitions are structured to match the
//  description in the RISC-V User-Level ISA specification as closely as
//  possible. For instance, the specification describes instructions with the
//  MSB (31st bit) on the left and the LSB (0th bit) on the right. This is
//  reflected in the order of parameters to each instruction class.
//
//  One area of divergence is in the description of immediates. The
//  specification describes immediate encoding in terms of bit-slicing
//  operations on the logical value represented. The immediate argument to
//  these instruction formats instead represents the bit sequence that will be
//  inserted into the instruction. e.g. although JAL's immediate is logically
//  a 21-bit value (where the LSB is always zero), we describe it as an imm20
//  to match how it is encoded.
//
//===----------------------------------------------------------------------===//

class FunnyarchCond<bits<3> val> {
  bits<3> Value = val;
}
def CondAlways     : FunnyarchCond<0>; // Execute unconditionally
def CondIfeq       : FunnyarchCond<1>; // Execute if zero flag is set
def CondIfneq      : FunnyarchCond<2>; // Execute if zero flag is not set
def CondIflt       : FunnyarchCond<3>; // Execute if carry flag is set
def CondIfgteq     : FunnyarchCond<4>; // Execute if carry flag is not set
def CondIfgt       : FunnyarchCond<5>; // Execute if both carry and zero flags are not set
def CondIflteq     : FunnyarchCond<6>; // Execute if zero flag or carry flag is set

class FunnyarchOpcodeX<bits<6> val> {
  bits<6> Value = val;
}
def OPC_NOP        : FunnyarchOpcodeX<0x00>;
def OPC_STRPI      : FunnyarchOpcodeX<0x01>;
def OPC_JMP        : FunnyarchOpcodeX<0x02>;
def OPC_RJMP       : FunnyarchOpcodeX<0x03>;
def OPC_MOV_E7     : FunnyarchOpcodeX<0x04>;
def OPC_MOV_E3     : FunnyarchOpcodeX<0x05>;
def OPC_LDR        : FunnyarchOpcodeX<0x06>;
def OPC_LDRI       : FunnyarchOpcodeX<0x07>;
def OPC_STR        : FunnyarchOpcodeX<0x08>;
def OPC_STRI       : FunnyarchOpcodeX<0x09>;
def OPC_JAL        : FunnyarchOpcodeX<0x0A>;
def OPC_RJAL       : FunnyarchOpcodeX<0x0B>;
def OPC_CMP_E7     : FunnyarchOpcodeX<0x0C>;
def OPC_CMP_E3     : FunnyarchOpcodeX<0x0D>;
def OPC_INT        : FunnyarchOpcodeX<0x0E>;
def OPC_ADD_E1     : FunnyarchOpcodeX<0x10>;
def OPC_ADD_E2     : FunnyarchOpcodeX<0x11>;
def OPC_ADD_E3     : FunnyarchOpcodeX<0x12>;
def OPC_SUB_E1     : FunnyarchOpcodeX<0x13>;
def OPC_SUB_E2     : FunnyarchOpcodeX<0x14>;
def OPC_SUB_E3     : FunnyarchOpcodeX<0x15>;
def OPC_SHL_E1     : FunnyarchOpcodeX<0x16>;
def OPC_SHL_E2     : FunnyarchOpcodeX<0x17>;
def OPC_SHR_E1     : FunnyarchOpcodeX<0x18>;
def OPC_SHR_E2     : FunnyarchOpcodeX<0x19>;
def OPC_SAR_E1     : FunnyarchOpcodeX<0x1A>;
def OPC_SAR_E2     : FunnyarchOpcodeX<0x1B>;
def OPC_AND_E1     : FunnyarchOpcodeX<0x1C>;
def OPC_AND_E2     : FunnyarchOpcodeX<0x1D>;
def OPC_AND_E3     : FunnyarchOpcodeX<0x1E>;
def OPC_OR_E1      : FunnyarchOpcodeX<0x1F>;
def OPC_OR_E2      : FunnyarchOpcodeX<0x20>;
def OPC_OR_E3      : FunnyarchOpcodeX<0x21>;
def OPC_XOR_E1     : FunnyarchOpcodeX<0x22>;
def OPC_XOR_E2     : FunnyarchOpcodeX<0x23>;
def OPC_XOR_E3     : FunnyarchOpcodeX<0x24>;
def OPC_NOT        : FunnyarchOpcodeX<0x25>;

// Format specifies the encoding used by the instruction. This is used by
// FunnyarchMCCodeEmitter to determine which form of fixup to use. These
// definitions must be kept in-sync with FunnyarchBaseInfo.h.
class InstFormatX<bits<3> val> {
  bits<3> Value = val;
}
def InstFormatPseudo  : InstFormatX<0>;
def InstFormatE1      : InstFormatX<1>;
def InstFormatE2      : InstFormatX<2>;
def InstFormatE3      : InstFormatX<3>;
def InstFormatE4      : InstFormatX<4>;
def InstFormatE5      : InstFormatX<5>;
def InstFormatE6      : InstFormatX<6>;
def InstFormatE7      : InstFormatX<7>;


class FUInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern, InstFormatX format>
    : Instruction {
  field bits<32> Inst;

  let Size = 4;

  bits<6> Opcode = 0;
  bits<3> Condition = 0;

  let Inst{5-0} = Opcode;
  let Inst{8-6} = Condition;

  let Namespace = "Funnyarch";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;

  let TSFlags{2-0} = format.Value;
}

class FUInstE7<bits<13> instrspecific, FunnyarchOpcodeX opcode, FunnyarchCond condition, string opcodestr, string argstr,
               dag outs, dag ins, list<dag> pattern>
    : FUInst<outs, ins, opcodestr, argstr, pattern, InstFormatE7> {
  bits<5> reg_src;
  bits<5> reg_tgt;

  let Inst{13-9} = reg_src;
  let Inst{18-14} = reg_tgt;
  let Inst{31-19} = instrspecific;

  let Opcode = opcode.Value;
  let Condition = condition.Value;
}

// Format specifies the encoding used by the instruction. This is used by
// FunnyarchMCCodeEmitter to determine which form of fixup to use. These
// definitions must be kept in-sync with FunnyarchBaseInfo.h.
class InstFormat<bits<5> val> {
  bits<5> Value = val;
}
def InstFormatR      : InstFormat<1>;
def InstFormatI      : InstFormat<3>;
def InstFormatU      : InstFormat<6>;

// The following opcode names match those given in Table 19.1 in the
// RISC-V User-level ISA specification ("RISC-V base opcode map").
class FunnyarchOpcode<bits<7> val> {
  bits<7> Value = val;
}
def OPC_LOAD      : FunnyarchOpcode<0b0000011>;
def OPC_LOAD_FP   : FunnyarchOpcode<0b0000111>;
def OPC_MISC_MEM  : FunnyarchOpcode<0b0001111>;
def OPC_OP_IMM    : FunnyarchOpcode<0b0010011>;
def OPC_AUIPC     : FunnyarchOpcode<0b0010111>;
def OPC_OP_IMM_32 : FunnyarchOpcode<0b0011011>;
def OPC_STORE     : FunnyarchOpcode<0b0100011>;
def OPC_STORE_FP  : FunnyarchOpcode<0b0100111>;
def OPC_AMO       : FunnyarchOpcode<0b0101111>;
def OPC_OP        : FunnyarchOpcode<0b0110011>;
def OPC_LUI       : FunnyarchOpcode<0b0110111>;
def OPC_OP_32     : FunnyarchOpcode<0b0111011>;
def OPC_MADD      : FunnyarchOpcode<0b1000011>;
def OPC_MSUB      : FunnyarchOpcode<0b1000111>;
def OPC_NMSUB     : FunnyarchOpcode<0b1001011>;
def OPC_NMADD     : FunnyarchOpcode<0b1001111>;
def OPC_OP_FP     : FunnyarchOpcode<0b1010011>;
def OPC_BRANCH    : FunnyarchOpcode<0b1100011>;
def OPC_JALR      : FunnyarchOpcode<0b1100111>;
def OPC_SYSTEM    : FunnyarchOpcode<0b1110011>;

class RWInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern, InstFormat format>
    : Instruction {
  field bits<32> Inst;

  let Size = 4;

  bits<7> Opcode = 0;

  let Inst{6-0} = Opcode;

  let Namespace = "Funnyarch";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;

  let TSFlags{4-0} = format.Value;
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, list<dag> pattern>
    : FUInst<outs, ins, "this is a pseudo instruction", "", pattern, InstFormatPseudo>,
      Sched<[]> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

// Instruction formats are listed in the order they appear in the RISC-V
// instruction set manual (R, I, S, B, U, J) with sub-formats (e.g. RWInstR4,
// RWInstRAtomic) sorted alphabetically.

class RWInstR<bits<7> funct7, bits<3> funct3, FunnyarchOpcode opcode, dag outs,
              dag ins, string opcodestr, string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatR> {
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RWInstI<bits<3> funct3, FunnyarchOpcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatI> {
  bits<12> imm12;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RWInstIShift<bit arithshift, bits<3> funct3, FunnyarchOpcode opcode,
                   dag outs, dag ins, string opcodestr, string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatI> {
  bits<6> shamt;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31} = 0;
  let Inst{30} = arithshift;
  let Inst{29-26} = 0;
  let Inst{25-20} = shamt;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RWInstU<FunnyarchOpcode opcode, dag outs, dag ins, string opcodestr,
              string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatU> {
  bits<20> imm20;
  bits<5> rd;

  let Inst{31-12} = imm20;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}
