//===---- FunnyarchISelDAGToDAG.h - A Dag to Dag Inst Selector for Funnyarch ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the Funnyarch target.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHISELDAGTODAG_H
#define LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHISELDAGTODAG_H

#include "FunnyarchSubtarget.h"
#include "FunnyarchTargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {
class FunnyarchDAGToDAGISel : public SelectionDAGISel {
public:
  explicit FunnyarchDAGToDAGISel(FunnyarchTargetMachine &TM, CodeGenOpt::Level OL)
      : SelectionDAGISel(TM, OL), Subtarget(nullptr) {}

  // Pass Name
  StringRef getPassName() const override {
    return "CPU0 DAG->DAG Pattern Instruction Selection";
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void Select(SDNode *Node) override;

#include "FunnyarchGenDAGISel.inc"

private:
  const FunnyarchSubtarget *Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_FUNNYARCH_FUNNYARCHISELDAGTODAG_H
