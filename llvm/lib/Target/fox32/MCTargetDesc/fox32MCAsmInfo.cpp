//===-- fox32MCAsmInfo.cpp - fox32 Asm properties ------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the fox32MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "fox32MCAsmInfo.h"
#include "llvm/ADT/Triple.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void fox32MCAsmInfo::anchor() {}

fox32MCAsmInfo::fox32MCAsmInfo(const Triple &TT) {
  CodePointerSize = CalleeSaveStackSlotSize = 4;
  AlignmentIsInBytes = false;
  Data8bitsDirective = "\t.byte\t";
  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = "\t.dword\t";
  ZeroDirective = "\t.space\t";
  CommentString = "#";
  SupportsDebugInformation = true;
  DwarfRegNumForCFI = true;
  ExceptionsType = ExceptionHandling::DwarfCFI;
}
