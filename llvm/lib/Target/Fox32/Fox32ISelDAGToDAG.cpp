//===-- Fox32ISelDAGToDAG.cpp - A Dag to Dag Inst Selector for Fox32 ------===//
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

#include "Fox32ISelDAGToDAG.h"
#include "Fox32Subtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

#define DEBUG_TYPE "fox32-isel"

bool Fox32DAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &static_cast<const Fox32Subtarget &>(MF.getSubtarget());
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void Fox32DAGToDAGISel::Select(SDNode *Node) {
  // If we have a custom node, we already have selected!
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(errs() << "== "; Node->dump(CurDAG); errs() << "\n");
    Node->setNodeId(-1);
    return;
  }

  // Instruction Selection not handled by the auto-generated tablegen selection
  // should be handled here.
  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  switch(Opcode) {
  case ISD::Constant: {
    auto ConstNode = cast<ConstantSDNode>(Node);
    if (ConstNode->isNullValue()) {
      SDValue New = CurDAG->getCopyFromReg(CurDAG->getEntryNode(), SDLoc(Node),
                                           Fox32::X0, MVT::i32);
      ReplaceNode(Node, New.getNode());
      return;
    }
    break;
  }
  default: break;
  }

  // Select the default instruction
  SelectCode(Node);
}
