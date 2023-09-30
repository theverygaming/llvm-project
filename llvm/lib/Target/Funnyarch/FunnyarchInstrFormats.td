//=== FunnyarchInstrFormats.td - Funnyarch Instruction Formats -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
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

class FunnyarchOpcode<bits<6> val> {
  bits<6> Value = val;
}
def OPC_NOP        : FunnyarchOpcode<0x00>;
def OPC_STRPI      : FunnyarchOpcode<0x01>;
def OPC_JMP        : FunnyarchOpcode<0x02>;
def OPC_RJMP       : FunnyarchOpcode<0x03>;
def OPC_MOV_E7     : FunnyarchOpcode<0x04>;
def OPC_MOV_E3     : FunnyarchOpcode<0x05>;
def OPC_LDR        : FunnyarchOpcode<0x06>;
def OPC_LDRI       : FunnyarchOpcode<0x07>;
def OPC_STR        : FunnyarchOpcode<0x08>;
def OPC_STRI       : FunnyarchOpcode<0x09>;
def OPC_JAL        : FunnyarchOpcode<0x0A>;
def OPC_RJAL       : FunnyarchOpcode<0x0B>;
def OPC_CMP_E7     : FunnyarchOpcode<0x0C>;
def OPC_CMP_E3     : FunnyarchOpcode<0x0D>;
def OPC_INT        : FunnyarchOpcode<0x0E>;
def OPC_ADD_E1     : FunnyarchOpcode<0x10>;
def OPC_ADD_E2     : FunnyarchOpcode<0x11>;
def OPC_ADD_E3     : FunnyarchOpcode<0x12>;
def OPC_SUB_E1     : FunnyarchOpcode<0x13>;
def OPC_SUB_E2     : FunnyarchOpcode<0x14>;
def OPC_SUB_E3     : FunnyarchOpcode<0x15>;
def OPC_SHL_E1     : FunnyarchOpcode<0x16>;
def OPC_SHL_E2     : FunnyarchOpcode<0x17>;
def OPC_SHR_E1     : FunnyarchOpcode<0x18>;
def OPC_SHR_E2     : FunnyarchOpcode<0x19>;
def OPC_SAR_E1     : FunnyarchOpcode<0x1A>;
def OPC_SAR_E2     : FunnyarchOpcode<0x1B>;
def OPC_AND_E1     : FunnyarchOpcode<0x1C>;
def OPC_AND_E2     : FunnyarchOpcode<0x1D>;
def OPC_AND_E3     : FunnyarchOpcode<0x1E>;
def OPC_OR_E1      : FunnyarchOpcode<0x1F>;
def OPC_OR_E2      : FunnyarchOpcode<0x20>;
def OPC_OR_E3      : FunnyarchOpcode<0x21>;
def OPC_XOR_E1     : FunnyarchOpcode<0x22>;
def OPC_XOR_E2     : FunnyarchOpcode<0x23>;
def OPC_XOR_E3     : FunnyarchOpcode<0x24>;
def OPC_NOT        : FunnyarchOpcode<0x25>;

// Format specifies the encoding used by the instruction. This is used by
// FunnyarchMCCodeEmitter to determine which form of fixup to use. These
// definitions must be kept in-sync with FunnyarchBaseInfo.h.
class InstFormat<bits<3> val> {
  bits<3> Value = val;
}
def InstFormatPseudo  : InstFormat<0>;
def InstFormatE1      : InstFormat<1>;
def InstFormatE2      : InstFormat<2>;
def InstFormatE3      : InstFormat<3>;
def InstFormatE4      : InstFormat<4>;
def InstFormatE5      : InstFormat<5>;
def InstFormatE6      : InstFormat<6>;
def InstFormatE7      : InstFormat<7>;


class FUInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern, InstFormat format>
    : Instruction {

  let Namespace = "Funnyarch";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;
  let Size = 4;

  bits<6> Opcode;
  bits<3> Condition;

  field bits<32> Inst;

  let Inst{5-0} = Opcode;
  let Inst{8-6} = Condition;

  let TSFlags{2-0} = format.Value;
}

class FUInstE1<bits<8> instrspecific, FunnyarchOpcode opcode, FunnyarchCond condition, string opcodestr, string argstr,
               dag outs, dag ins, list<dag> pattern>
    : FUInst<outs, ins, opcodestr, argstr, pattern, InstFormatE7> {
  bits<5> rsrc1;
  bits<5> rsrc2;
  bits<5> rtgt;

  let Inst{13-9} = rsrc1;
  let Inst{18-14} = rsrc2;
  let Inst{23-19} = rtgt;
  let Inst{31-24} = instrspecific;

  let Opcode = opcode.Value;
  let Condition = condition.Value;
}

class FUInstE7<bits<13> instrspecific, FunnyarchOpcode opcode, FunnyarchCond condition, string opcodestr, string argstr,
               dag outs, dag ins, list<dag> pattern>
    : FUInst<outs, ins, opcodestr, argstr, pattern, InstFormatE7> {
  bits<5> rsrc;
  bits<5> rtgt;

  let Inst{13-9} = rsrc;
  let Inst{18-14} = rtgt;
  let Inst{31-19} = instrspecific;

  let Opcode = opcode.Value;
  let Condition = condition.Value;
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, list<dag> pattern>
    : FUInst<outs, ins, "this is a pseudo instruction", "", pattern, InstFormatPseudo>,
      Sched<[]> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}
