//=== Fox32MachineFunctionInfo.h - Private data used for Fox32 ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Fox32 specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32MACHINEFUNCTION_H
#define LLVM_LIB_TARGET_FOX32_FOX32MACHINEFUNCTION_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// Fox32FunctionInfo - This class is derived from MachineFunction private
/// Fox32 target-specific information for each MachineFunction.
class Fox32FunctionInfo : public MachineFunctionInfo {
private:
  MachineFunction &MF;

public:
  Fox32FunctionInfo(MachineFunction &MF) : MF(MF) {}
};

} // end of namespace llvm

#endif // end LLVM_LIB_TARGET_FOX32_FOX32MACHINEFUNCTION_H
