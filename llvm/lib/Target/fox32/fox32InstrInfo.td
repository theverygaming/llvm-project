//== fox32InstrInfo.td - Target Description for fox32 -*- tablegen -*-//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the fox32 instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

/// Define scheduler resources associated with def operands.
def WriteIALU       : SchedWrite;    // 32 or 64-bit integer ALU operations
def ReadIALU        : SchedRead;

class InstFormat<bits<5> val> {
  bits<5> Value = val;
}
def InstFormatR      : InstFormat<1>;

class RWInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern, InstFormat format>
    : Instruction {
  field bits<32> Inst;
  // SoftFail is a field the disassembler can use to provide a way for
  // instructions to not match without killing the whole decode process. It is
  // mainly used for ARM, but Tablegen expects this field to exist or it fails
  // to build the decode table.
  field bits<32> SoftFail = 0;
  let Size = 4;

  bits<7> Opcode = 0;

  let Inst{6-0} = Opcode;

  let Namespace = "fox32";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;

  let TSFlags{4-0} = format.Value;
}

class fox32Opcode<bits<7> val> {
  bits<7> Value = val;
}
def OPC_LOAD      : fox32Opcode<0b0000011>;
def OPC_LOAD_FP   : fox32Opcode<0b0000111>;
def OPC_MISC_MEM  : fox32Opcode<0b0001111>;
def OPC_OP_IMM    : fox32Opcode<0b0010011>;
def OPC_AUIPC     : fox32Opcode<0b0010111>;
def OPC_OP_IMM_32 : fox32Opcode<0b0011011>;
def OPC_STORE     : fox32Opcode<0b0100011>;
def OPC_STORE_FP  : fox32Opcode<0b0100111>;
def OPC_AMO       : fox32Opcode<0b0101111>;
def OPC_OP        : fox32Opcode<0b0110011>;
def OPC_LUI       : fox32Opcode<0b0110111>;
def OPC_OP_32     : fox32Opcode<0b0111011>;
def OPC_MADD      : fox32Opcode<0b1000011>;
def OPC_MSUB      : fox32Opcode<0b1000111>;
def OPC_NMSUB     : fox32Opcode<0b1001011>;
def OPC_NMADD     : fox32Opcode<0b1001111>;
def OPC_OP_FP     : fox32Opcode<0b1010011>;
def OPC_BRANCH    : fox32Opcode<0b1100011>;
def OPC_JALR      : fox32Opcode<0b1100111>;
def OPC_JAL       : fox32Opcode<0b1101111>;
def OPC_SYSTEM    : fox32Opcode<0b1110011>;

// Instruction formats are listed in the order they appear in the RISC-V
// instruction set manual (R, I, S, B, U, J) with sub-formats (e.g. RWInstR4,
// RWInstRAtomic) sorted alphabetically.

class RWInstR<bits<7> funct7, bits<3> funct3, fox32Opcode opcode, dag outs,
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

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class ALU_rr<bits<7> funct7, bits<3> funct3, string opcodestr>
    : RWInstR<funct7, funct3, OPC_OP, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
              opcodestr, "$rd, $rs1, $rs2">;

def ADD  : ALU_rr<0b0000000, 0b000, "add">,
           Sched<[WriteIALU, ReadIALU, ReadIALU]>;

let isReturn = 1, isBarrier = 1, isTerminator = 1 in
def RET : RWInstR<0b0000001, 0b000, OPC_OP, (outs),
              (ins), "ret", "">,
          Sched<[WriteIALU, ReadIALU, ReadIALU]>;

let hasSideEffects = 0, mayLoad = 1, mayStore = 1 in
def MOV : RWInstR<0b0000010, 0b000, OPC_OP, (outs GPR:$rd),
              (ins GPR:$rs1), "mov", "$rd, $rs1">,
          Sched<[WriteIALU, ReadIALU, ReadIALU]>;
