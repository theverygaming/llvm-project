//=- fox32ISelDAGToDAG.cpp - A dag to dag inst selector for fox32 -===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the fox32 target.
//
//===----------------------------------------------------------------------===//

#include "fox32ISelDAGToDAG.h"
#include "MCTargetDesc/fox32MCTargetDesc.h"
#include "fox32ISelLowering.h"
#include "llvm/Support/KnownBits.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-isel"

void fox32DAGToDAGISel::Select(SDNode *Node) {
  unsigned Opcode = Node->getOpcode();

  Node->dumprFull();
  puts("");

  // ????
  if (Opcode == 398) {
    Node->setNodeId(-1);
    printf("RETURN %s:%s:%d\n", __func__, __FILE__, __LINE__);
    return;
  }

  // If we have a custom node, we already have selected!
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(errs() << "== "; Node->dump(CurDAG); errs() << "\n");
    Node->setNodeId(-1);
    printf("RETURN %s:%s:%d\n", __func__, __FILE__, __LINE__);
    return;
  }

  // Instruction Selection not handled by the auto-generated tablegen selection
  // should be handled here.
  switch (Opcode) {
  default:
    break;
  case ISD::Constant: {
    printf("!! %s:%s:%d\n", __func__, __FILE__, __LINE__);
    break;
  }
  case ISD::FrameIndex: {
    printf("!! %s:%s:%d\n", __func__, __FILE__, __LINE__);
    break;
  }
  }

  if (Node->isTargetOpcode()) {
    printf("Node->isTargetOpcode() yes\n");
  }

  printf("opc: %s (%u)\n", Node->getOperationName().c_str(), Node->getOpcode());

  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);

  // Select the default instruction
  SelectCode(Node);
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  Node->dumprFull();
  puts("");
  printf("RETURN %s:%s:%d\n", __func__, __FILE__, __LINE__);
}

// This pass converts a legalized DAG into a fox32-specific DAG, ready
// for instruction scheduling.
FunctionPass *llvm::createfox32ISelDag(fox32TargetMachine &TM) {
  printf("%s:%s:%d\n", __func__, __FILE__, __LINE__);
  return new fox32DAGToDAGISel(TM);
}
