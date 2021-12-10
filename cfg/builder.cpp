
#include "builder.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/CFGDiff.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

char CfgBuilder::ID = 0;
bool CfgBuilder::runOnModule(Module& module) {
  auto f_main = module.getFunction("main");
  //errs() << "entry function: " << f_main->getName() << "\n";
  printCfg(f_main);
  return /*modified=*/false;
}

void CfgBuilder::printCfg(const ::llvm::BasicBlock* bb) {
  //errs() << "bb name :" << bb->getName() << "\n";
  //errs() << *bb << "\n";
  for (const auto& instruction : *bb) {  // traverse all callb sites
    //errs() << instruction << "\n";
     errs() << instruction.getOpcodeName(instruction.getOpcode()) << "\n";

    if (auto* callInstruction = ::llvm::dyn_cast<const ::llvm::CallInst>(&instruction)) {
      const auto calledFunction = callInstruction->getCalledFunction();
      if (calledFunction) {
        // TODO: check indirect recursive call
        if (calledFunction == bb->getParent()) {
          errs() << "direct recursive call site , stop.\n";
        } else {
          errs() << "call site: " << calledFunction->getName() << "\n";
          const auto& entry = calledFunction->getEntryBlock();
          printCfg(&entry);
        }
      }
    } else if (auto* branchInstruction = ::llvm::dyn_cast<::llvm::BranchInst>(&instruction)) {  // branch instruction
      errs() << "branch inst. \n";
      for (auto bb1 : branchInstruction->successors()) {
        printCfg(bb1);
      }
    }
  }
}

void CfgBuilder::printCfg(const Function* f) {
  //f->viewCFG();
  const auto& entry = f->getEntryBlock();
  errs() << "entry bb: " << entry.getName() << "\n"
         << "terminator:" << *entry.getTerminator() << "\n";
  printCfg(&entry);
}