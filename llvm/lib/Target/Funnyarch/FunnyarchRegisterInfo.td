//===-- FunnyarchRegisterInfo.td - Funnyarch Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the funnyarch register file
//===----------------------------------------------------------------------===//

let Namespace = "Funnyarch" in {
class FunnyarchReg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let AltNames = alt;
}
} // end Namespace

// GP registers
def R0  : FunnyarchReg<0, "r0",  []>, DwarfRegNum<[0]>;
def R1  : FunnyarchReg<1, "r1",  []>, DwarfRegNum<[1]>;
def R2  : FunnyarchReg<2, "r2",  []>, DwarfRegNum<[2]>;
def R3  : FunnyarchReg<3, "r3",  []>, DwarfRegNum<[3]>;
def R4  : FunnyarchReg<4, "r4",  []>, DwarfRegNum<[4]>;
def R5  : FunnyarchReg<5, "r5",  []>, DwarfRegNum<[5]>;
def R6  : FunnyarchReg<6, "r6",  []>, DwarfRegNum<[6]>;
def R7  : FunnyarchReg<7, "r7",  []>, DwarfRegNum<[7]>;
def R8  : FunnyarchReg<8, "r8",  []>, DwarfRegNum<[8]>;
def R9  : FunnyarchReg<9, "r9",  []>, DwarfRegNum<[9]>;
def R10 : FunnyarchReg<10,"r10", []>, DwarfRegNum<[10]>;
def R11 : FunnyarchReg<11,"r11", []>, DwarfRegNum<[11]>;
def R12 : FunnyarchReg<12,"r12", []>, DwarfRegNum<[12]>;
def R13 : FunnyarchReg<13,"r13", []>, DwarfRegNum<[13]>;
def R14 : FunnyarchReg<14,"r14", []>, DwarfRegNum<[14]>;
def R15 : FunnyarchReg<15,"r15", []>, DwarfRegNum<[15]>;
def R16 : FunnyarchReg<16,"r16", []>, DwarfRegNum<[16]>;
def R17 : FunnyarchReg<17,"r17", []>, DwarfRegNum<[17]>;
def R18 : FunnyarchReg<18,"r18", []>, DwarfRegNum<[18]>;
def R19 : FunnyarchReg<19,"r19", []>, DwarfRegNum<[19]>;
def R20 : FunnyarchReg<20,"r20", []>, DwarfRegNum<[20]>;
def R21 : FunnyarchReg<21,"r21", []>, DwarfRegNum<[21]>;
def R22 : FunnyarchReg<22,"r22", []>, DwarfRegNum<[22]>;
def R23 : FunnyarchReg<23,"r23", []>, DwarfRegNum<[23]>;
def R24 : FunnyarchReg<24,"r24", []>, DwarfRegNum<[24]>;
def R25 : FunnyarchReg<25,"r25", []>, DwarfRegNum<[25]>;

// special registers
def RFP : FunnyarchReg<26,"rfp", []>, DwarfRegNum<[26]>;
def RIPTR : FunnyarchReg<27,"iptr", []>, DwarfRegNum<[27]>;
def RLR : FunnyarchReg<28,"lr", []>, DwarfRegNum<[28]>;
def RSP : FunnyarchReg<29,"rsp", []>, DwarfRegNum<[29]>;
def RIP : FunnyarchReg<30,"rip", []>, DwarfRegNum<[30]>;
def RF : FunnyarchReg<31,"rf", []>, DwarfRegNum<[31]>;

// funnyarch calling convention: // FIXME: calling convention needs updates
// caller saves r0-r7
// callee saves: r8-r31
// args passed in: r0-r7 and then on stack
// return value in r0

// The order of registers represents the preferred allocation sequence.
// Registers are listed in the order caller-save, callee-save, specials.
def GPR : RegisterClass<"Funnyarch", [i32], 32, (add
    (sequence "R%u", 0, 7),
    (sequence "R%u", 8, 25),
    RFP, RIPTR, RLR, RSP, RIP, RF
  )>;
