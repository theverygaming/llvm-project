//===-- Fox32MCAsmInfo.cpp - Fox32 Asm Properties -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the Fox32MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "Fox32MCAsmInfo.h"

#include "llvm/ADT/Triple.h"

using namespace llvm;

void Fox32MCAsmInfo::anchor() { }

Fox32MCAsmInfo::Fox32MCAsmInfo(const Triple &TheTriple) {
  // This architecture is little endian only
  IsLittleEndian = false;

  AlignmentIsInBytes          = false;
  Data16bitsDirective         = "\t.hword\t";
  Data32bitsDirective         = "\t.word\t";
  Data64bitsDirective         = "\t.dword\t";

  PrivateGlobalPrefix         = ".L";
  PrivateLabelPrefix          = ".L";

  LabelSuffix                 = ":";

  CommentString               = ";";

  ZeroDirective               = "\t.zero\t";

  UseAssignmentForEHBegin     = true;

  SupportsDebugInformation    = true;
  ExceptionsType              = ExceptionHandling::DwarfCFI;
  DwarfRegNumForCFI           = true;
}
