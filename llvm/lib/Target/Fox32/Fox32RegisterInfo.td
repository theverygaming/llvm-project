//===-- Fox32RegisterInfo.td - Fox32 Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the fox32 register file
//===----------------------------------------------------------------------===//

let Namespace = "Fox32" in {
class Fox32Reg<bits<8> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{7-0} = Enc;
  let AltNames = alt;
}
} // end Namespace

// GP registers
def R0  : Fox32Reg<0, "r0",  []>, DwarfRegNum<[0]>;
def R1  : Fox32Reg<1, "r1",  []>, DwarfRegNum<[1]>;
def R2  : Fox32Reg<2, "r2",  []>, DwarfRegNum<[2]>;
def R3  : Fox32Reg<3, "r3",  []>, DwarfRegNum<[3]>;
def R4  : Fox32Reg<4, "r4",  []>, DwarfRegNum<[4]>;
def R5  : Fox32Reg<5, "r5",  []>, DwarfRegNum<[5]>;
def R6  : Fox32Reg<6, "r6",  []>, DwarfRegNum<[6]>;
def R7  : Fox32Reg<7, "r7",  []>, DwarfRegNum<[7]>;
def R8  : Fox32Reg<8, "r8",  []>, DwarfRegNum<[8]>;
def R9  : Fox32Reg<9, "r9",  []>, DwarfRegNum<[9]>;
def R10 : Fox32Reg<10,"r10", []>, DwarfRegNum<[10]>;
def R11 : Fox32Reg<11,"r11", []>, DwarfRegNum<[11]>;
def R12 : Fox32Reg<12,"r12", []>, DwarfRegNum<[12]>;
def R13 : Fox32Reg<13,"r13", []>, DwarfRegNum<[13]>;
def R14 : Fox32Reg<14,"r14", []>, DwarfRegNum<[14]>;
def R15 : Fox32Reg<15,"r15", []>, DwarfRegNum<[15]>;
def R16 : Fox32Reg<16,"r16", []>, DwarfRegNum<[16]>;
def R17 : Fox32Reg<17,"r17", []>, DwarfRegNum<[17]>;
def R18 : Fox32Reg<18,"r18", []>, DwarfRegNum<[18]>;
def R19 : Fox32Reg<19,"r19", []>, DwarfRegNum<[19]>;
def R20 : Fox32Reg<20,"r20", []>, DwarfRegNum<[20]>;
def R21 : Fox32Reg<21,"r21", []>, DwarfRegNum<[21]>;
def R22 : Fox32Reg<22,"r22", []>, DwarfRegNum<[22]>;
def R23 : Fox32Reg<23,"r23", []>, DwarfRegNum<[23]>;
def R24 : Fox32Reg<24,"r24", []>, DwarfRegNum<[24]>;
def R25 : Fox32Reg<25,"r25", []>, DwarfRegNum<[25]>;
def R26 : Fox32Reg<26,"r26", []>, DwarfRegNum<[26]>;
def R27 : Fox32Reg<27,"r27", []>, DwarfRegNum<[27]>;
def R28 : Fox32Reg<28,"r28", []>, DwarfRegNum<[28]>;
def R29 : Fox32Reg<29,"r29", []>, DwarfRegNum<[29]>;
def R30 : Fox32Reg<30,"r30", []>, DwarfRegNum<[30]>;
def R31 : Fox32Reg<31,"r31", []>, DwarfRegNum<[31]>; // used for loop and rloop instructions

// special registers
def RSP : Fox32Reg<32,"rsp", ["sp"]>, DwarfRegNum<[32]>;
def RESP : Fox32Reg<33,"resp", []>, DwarfRegNum<[33]>;
def RFP : Fox32Reg<34,"rfp", ["fp"]>, DwarfRegNum<[34]>;

// fox32 calling convention:
// caller saves r0-r7
// callee saves: r8-r31
// args passed in: r0-r7 and then on stack
// return value in r0

// The order of registers represents the preferred allocation sequence.
// Registers are listed in the order caller-save, callee-save, specials.
def GPR : RegisterClass<"Fox32", [i32], 32, (add
    (sequence "R%u", 0, 7),
    (sequence "R%u", 8, 31)
  )>;
