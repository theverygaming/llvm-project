include "llvm/Target/Target.td"

include "fox32RegisterInfo.td"
include "fox32CallingConv.td"
include "fox32InstrInfo.td"

def : ProcessorModel<"fox32", NoSchedModel, []>; // TODO: figure out what NoSchedModel means

def fox32InstrInfo : InstrInfo;

def fox32AsmWriter : AsmWriter {
  int PassSubtarget = 1;
}

def fox32 : Target {
  let InstructionSet = fox32InstrInfo;
  let AssemblyWriters = [fox32AsmWriter];
}
