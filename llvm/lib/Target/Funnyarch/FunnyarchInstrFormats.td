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

class FunnyarchOpType<bits<2> val> {
  bits<2> Value = val;
}
def OpTypeReg      : FunnyarchOpType<0>; // Register
def OpTypeRegPtr   : FunnyarchOpType<1>; // Register pointer
def OpTypeImm      : FunnyarchOpType<2>; // Immediate
def OpTypeImmPtr   : FunnyarchOpType<3>; // Immediate pointer

class FunnyarchOpSize<bits<2> val> {
  bits<2> Value = val;
}
def OpSizeByte     : FunnyarchOpSize<0>; // 8  bits
def OpSizeHalf     : FunnyarchOpSize<1>; // 16 bits
def OpSizeWord     : FunnyarchOpSize<2>; // 32 bits

class FunnyarchCond<bits<3> val> {
  bits<3> Value = val;
}
def CondAlways     : FunnyarchCond<0>; // Execute unconditionally
def CondIfz        : FunnyarchCond<1>; // Execute if zero flag is set
def CondIfnz       : FunnyarchCond<2>; // Execute if zero flag is not set
def CondIfc        : FunnyarchCond<3>; // Execute if carry flag is set
def CondIfnc       : FunnyarchCond<4>; // Execute if carry flag is not set
def CondIfgt       : FunnyarchCond<5>; // Execute if neither zero flag nor carry flag is set
def CondIflteq     : FunnyarchCond<6>; // Execute if zero flag or carry flag is set

class FunnyarchOpcodeX<bits<6> val> {
  bits<6> Value = val;
}
def OPC_NOP        : FunnyarchOpcodeX<0x00>;
def OPC_ADD        : FunnyarchOpcodeX<0x01>;
def OPC_MUL        : FunnyarchOpcodeX<0x02>;
def OPC_AND        : FunnyarchOpcodeX<0x03>;
def OPC_SLA        : FunnyarchOpcodeX<0x04>;
def OPC_SRA        : FunnyarchOpcodeX<0x05>;
def OPC_BSE        : FunnyarchOpcodeX<0x06>;
def OPC_CMP        : FunnyarchOpcodeX<0x07>;
def OPC_JMP        : FunnyarchOpcodeX<0x08>;
def OPC_RJMP       : FunnyarchOpcodeX<0x09>;
def OPC_PUSH       : FunnyarchOpcodeX<0x0A>;
def OPC_IN         : FunnyarchOpcodeX<0x0B>;
def OPC_ISE        : FunnyarchOpcodeX<0x0C>;
def OPC_MSE        : FunnyarchOpcodeX<0x0D>;
def OPC_HALT       : FunnyarchOpcodeX<0x10>;
def OPC_INC        : FunnyarchOpcodeX<0x11>;
def OPC_OR         : FunnyarchOpcodeX<0x13>;
def OPC_IMUL       : FunnyarchOpcodeX<0x14>;
def OPC_SRL        : FunnyarchOpcodeX<0x15>;
def OPC_BCL        : FunnyarchOpcodeX<0x16>;
def OPC_MOV        : FunnyarchOpcodeX<0x17>;
def OPC_CALL       : FunnyarchOpcodeX<0x18>;
def OPC_RCALL      : FunnyarchOpcodeX<0x19>;
def OPC_POP        : FunnyarchOpcodeX<0x1A>;
def OPC_OUT        : FunnyarchOpcodeX<0x1B>;
def OPC_ICL        : FunnyarchOpcodeX<0x1C>;
def OPC_MCL        : FunnyarchOpcodeX<0x1D>;
def OPC_BRK        : FunnyarchOpcodeX<0x20>;
def OPC_SUB        : FunnyarchOpcodeX<0x21>;
def OPC_DIV        : FunnyarchOpcodeX<0x22>;
def OPC_XOR        : FunnyarchOpcodeX<0x23>;
def OPC_ROL        : FunnyarchOpcodeX<0x24>;
def OPC_ROR        : FunnyarchOpcodeX<0x25>;
def OPC_BTS        : FunnyarchOpcodeX<0x26>;
def OPC_MOVZ       : FunnyarchOpcodeX<0x27>;
def OPC_LOOP       : FunnyarchOpcodeX<0x28>;
def OPC_RLOOP      : FunnyarchOpcodeX<0x29>;
def OPC_RET        : FunnyarchOpcodeX<0x2A>;
def OPC_INT        : FunnyarchOpcodeX<0x2C>;
def OPC_TLB        : FunnyarchOpcodeX<0x2D>;
def OPC_DEC        : FunnyarchOpcodeX<0x31>;
def OPC_REM        : FunnyarchOpcodeX<0x32>;
def OPC_NOT        : FunnyarchOpcodeX<0x33>;
def OPC_IDIV       : FunnyarchOpcodeX<0x34>;
def OPC_IREM       : FunnyarchOpcodeX<0x35>;
def OPC_RTA        : FunnyarchOpcodeX<0x39>;
def OPC_RETI       : FunnyarchOpcodeX<0x3A>;
def OPC_FLP        : FunnyarchOpcodeX<0x3D>;

class InstFormatX<bits<5> val> {
  bits<5> Value = val;
}
def InstFormatPseudoX : InstFormatX<0>;

// no operands
class FunnyarchInst_None<dag outs, dag ins, list<dag> pattern, string opcodestr, string argstr,
             FunnyarchOpcodeX opcode,
             FunnyarchCond condition,
             FunnyarchOpSize opsize>
    : Instruction {
  let Namespace      = "Funnyarch";
  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString      = opcodestr # " " # argstr;
  let Pattern        = pattern;

  // control word
  bits<2> SrcType = 0;
  bits<2> DstType = 0;
  bits<3> Condition = condition.Value;
  bits<6> Opcode = opcode.Value;
  bits<2> OpSize = opsize.Value;

  field bits<16> Inst;
  let Size = 2;

  let Inst{1-0} = SrcType;
  let Inst{3-2} = DstType;
  let Inst{6-4} = Condition;
  let Inst{7} = 0;
  let Inst{13-8} = Opcode;
  let Inst{15-14} = OpSize;
}

// src only - imm8
class FunnyarchInst_srcimm8<dag outs, dag ins, list<dag> pattern, string opcodestr, string argstr,
             FunnyarchOpcodeX opcode,
             FunnyarchCond condition,
             bits<8> src>
    : Instruction {
  let Namespace      = "Funnyarch";
  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString      = opcodestr # " " # argstr;
  let Pattern        = pattern;

  // control word
  bits<2> SrcType = OpTypeImm.Value;
  bits<2> DstType = 0;
  bits<3> Condition = condition.Value;
  bits<6> Opcode = opcode.Value;
  bits<2> OpSize = OpSizeByte.Value;

  field bits<24> Inst;
  let Size = 3;

  let Inst{1-0} = SrcType;
  let Inst{3-2} = DstType;
  let Inst{6-4} = Condition;
  let Inst{7} = 0;
  let Inst{13-8} = Opcode;
  let Inst{15-14} = OpSize;
  let Inst{23-16} = src;
}

// src+dst - immptr32
class FunnyarchInst_srcimmptr32dstimmptr32<dag outs, dag ins, list<dag> pattern, string opcodestr, string argstr,
             FunnyarchOpcodeX opcode,
             FunnyarchCond condition>
    : Instruction {

  bits<32> src;
  bits<32> dst;
  let Namespace      = "Funnyarch";
  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString      = opcodestr # " " # argstr;
  let Pattern        = pattern;

  // control word
  bits<2> SrcType = OpTypeImmPtr.Value;
  bits<2> DstType = OpTypeImmPtr.Value;
  bits<3> Condition = condition.Value;
  bits<6> Opcode = opcode.Value;
  bits<2> OpSize = OpSizeWord.Value;

  field bits<80> Inst;
  let Size = 10;

  let Inst{1-0} = SrcType;
  let Inst{3-2} = DstType;
  let Inst{6-4} = Condition;
  let Inst{7} = 0;
  let Inst{13-8} = Opcode;
  let Inst{15-14} = OpSize;
  let Inst{47-16} = src;
  let Inst{79-48} = dst;
}


// Format specifies the encoding used by the instruction. This is used by
// FunnyarchMCCodeEmitter to determine which form of fixup to use. These
// definitions must be kept in-sync with FunnyarchBaseInfo.h.
class InstFormat<bits<5> val> {
  bits<5> Value = val;
}
def InstFormatPseudo : InstFormat<0>;
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
def OPC_JAL       : FunnyarchOpcode<0b1101111>;
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
    : FunnyarchInst_None<outs, ins, pattern, "this is a pseudo instruction", "", OPC_NOP, CondAlways, OpSizeWord>,
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
