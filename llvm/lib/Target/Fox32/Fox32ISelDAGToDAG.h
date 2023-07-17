//===---- Fox32ISelDAGToDAG.h - A Dag to Dag Inst Selector for Fox32 ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the Fox32 target.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_FOX32_FOX32ISELDAGTODAG_H
#define LLVM_LIB_TARGET_FOX32_FOX32ISELDAGTODAG_H

#include "Fox32Subtarget.h"
#include "Fox32TargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {
class Fox32DAGToDAGISel : public SelectionDAGISel {
public:
  explicit Fox32DAGToDAGISel(Fox32TargetMachine &TM, CodeGenOpt::Level OL)
      : SelectionDAGISel(TM, OL), Subtarget(nullptr) {}

  // Pass Name
  StringRef getPassName() const override {
    return "CPU0 DAG->DAG Pattern Instruction Selection";
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void Select(SDNode *Node) override;

#include "Fox32GenDAGISel.inc"

private:
  const Fox32Subtarget *Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_FOX32_FOX32ISELDAGTODAG_H
