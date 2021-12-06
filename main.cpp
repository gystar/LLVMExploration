#include <stdio.h>
#include <string>
#include <iostream>
#include "cfg/builder.h"

//#include <google/protobuf/def.inc>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

int main()
{
  printf("Hello llvm! \n");
  ::llvm::legacy::PassManager passManager;
  ::llvm::PassManagerBuilder passManagerBuilder;
  // passManagerBuilder.OptLevel = options.opt_level();
  passManagerBuilder.populateModulePassManager(passManager);

  // Create a graph builder pass. Ownership of this pointer is transferred to
  auto cfg_pass = new CfgBuilder();

  passManager.add(cfg_pass);
  //llvm::Instruction()
  ::llvm::SMDiagnostic error;
  ::llvm::LLVMContext ctx;
  auto module = ::llvm::parseIRFile("./data/test1.bc", error, ctx);
  passManager.run(*module);

  return 0;
}