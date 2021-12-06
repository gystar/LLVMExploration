
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
  printCfg(f_main);
  return /*modified=*/false;
}

void CfgBuilder::printCfg(const ::llvm::BasicBlock* bb) {
  errs() << "bb name :" << bb->getName() << "\n";
  for (const auto& instruction : *bb) {  // traverse all callb sites
    // errs() << instruction << "\n";
    // If the instruction is a call, record the call site, which we will use
    // later to create all edges..
    if (auto* callInstruction = ::llvm::dyn_cast<const ::llvm::CallInst>(&instruction)) {
      const auto calledFunction = callInstruction->getCalledFunction();
      // TODO(github.com/ChrisCummins/ProGraML/issues/46): Should we handle
      // the case when getCalledFunction() is nil?
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
    } else if (auto* branchInstruction = ::llvm::dyn_cast<::llvm::BranchInst>(bb)) {  // branch instruction
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