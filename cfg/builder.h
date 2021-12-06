#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

class CfgBuilder : public ::llvm::ModulePass {
 public:
  static char ID;

  CfgBuilder() : ModulePass(ID) {}
  ~CfgBuilder(){};

  bool runOnModule(::llvm::Module& module) override;

  void printCfg(const ::llvm::Function* f);
  void printCfg(const ::llvm::BasicBlock* bb);
};
