//=== FunnyarchMachineFunctionInfo.h - Private data used for Funnyarch ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Funnyarch specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHMACHINEFUNCTION_H
#define LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHMACHINEFUNCTION_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// FunnyarchFunctionInfo - This class is derived from MachineFunction private
/// Funnyarch target-specific information for each MachineFunction.
class FunnyarchFunctionInfo : public MachineFunctionInfo {
private:
  MachineFunction &MF;

public:
  FunnyarchFunctionInfo(MachineFunction &MF) : MF(MF) {}
};

} // end of namespace llvm

#endif // end LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHMACHINEFUNCTION_H
