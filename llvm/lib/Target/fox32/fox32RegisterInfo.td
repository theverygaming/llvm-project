//===-- fox32RegisterInfo.td - fox32 Register defs -*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the fox32 register files
//===----------------------------------------------------------------------===//

let Namespace = "fox32" in {
class fox32Reg<bits<16> Enc, string n, list<string> alt = []>
    : Register<n> {
  let HWEncoding = Enc;
  let AltNames = alt;
}

let FallbackRegAltNameIndex = NoRegAltName in
def RegAliasName : RegAltNameIndex;
} // Namespace = "fox32"


// Integer registers

let RegAltNameIndices = [RegAliasName] in {
  def X0  : fox32Reg<0,  "r0", ["zero"]>, DwarfRegNum<[0]>;
  def X1  : fox32Reg<1,  "r1", ["ra"]>, DwarfRegNum<[1]>;
  def X2  : fox32Reg<2,  "r2", ["tp"]>, DwarfRegNum<[2]>;
  def X3  : fox32Reg<3,  "r3", ["sp"]>, DwarfRegNum<[3]>;
  def X4  : fox32Reg<4,  "r4", ["a0"]>, DwarfRegNum<[4]>;
  def X5  : fox32Reg<5,  "r5", ["a1"]>, DwarfRegNum<[5]>;
  def X6  : fox32Reg<6,  "r6", ["a2"]>, DwarfRegNum<[6]>;
  def X7  : fox32Reg<7,  "r7", ["a3"]>, DwarfRegNum<[7]>;
  def X8  : fox32Reg<8,  "r8", ["a4"]>, DwarfRegNum<[8]>;
  def X9  : fox32Reg<9,  "r9", ["a5"]>, DwarfRegNum<[9]>;
  def X10 : fox32Reg<10, "r10", ["a6"]>, DwarfRegNum<[10]>;
  def X11 : fox32Reg<11, "r11", ["a7"]>, DwarfRegNum<[11]>;
  def X12 : fox32Reg<12, "r12", ["t0"]>, DwarfRegNum<[12]>;
  def X13 : fox32Reg<13, "r13", ["t1"]>, DwarfRegNum<[13]>;
  def X14 : fox32Reg<14, "r14", ["t2"]>, DwarfRegNum<[14]>;
  def X15 : fox32Reg<15, "r15", ["t3"]>, DwarfRegNum<[15]>;
  def X16 : fox32Reg<16, "r16", ["t4"]>, DwarfRegNum<[16]>;
  def X17 : fox32Reg<17, "r17", ["t5"]>, DwarfRegNum<[17]>;
  def X18 : fox32Reg<18, "r18", ["t6"]>, DwarfRegNum<[18]>;
  def X19 : fox32Reg<19, "r19", ["t7"]>, DwarfRegNum<[19]>;
  def X20 : fox32Reg<20, "r20", ["t8"]>, DwarfRegNum<[20]>;
  def X21 : fox32Reg<21, "r21", [""]>, DwarfRegNum<[21]>;
  def X22 : fox32Reg<22, "r22", ["fp", "s9"]>, DwarfRegNum<[22]>;
  def X23 : fox32Reg<23, "r23", ["s0"]>, DwarfRegNum<[23]>;
  def X24 : fox32Reg<24, "r24", ["s1"]>, DwarfRegNum<[24]>;
  def X25 : fox32Reg<25, "r25", ["s2"]>, DwarfRegNum<[25]>;
  def X26 : fox32Reg<26, "r26", ["s3"]>, DwarfRegNum<[26]>;
  def X27 : fox32Reg<27, "r27", ["s4"]>, DwarfRegNum<[27]>;
  def X28 : fox32Reg<28, "r28", ["s5"]>, DwarfRegNum<[28]>;
  def X29 : fox32Reg<29, "r29", ["s6"]>, DwarfRegNum<[29]>;
  def X30 : fox32Reg<30, "r30", ["s7"]>, DwarfRegNum<[30]>;
  def X31 : fox32Reg<31, "r31", ["s8"]>, DwarfRegNum<[31]>;
} // RegAltNameIndices = [RegAliasName]


def GPR : RegisterClass<"fox32", [i32], 32, (add
    (sequence "X%u", 0, 31)
  )>;

