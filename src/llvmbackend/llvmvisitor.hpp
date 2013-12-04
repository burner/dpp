#pragma once

#include <stdexcept>
#include <stack>

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>

#include <visitor.hpp>

class LLVMVisitorException : public std::exception {
public:
	LLVMVisitorException(const std::string&,Loc);
	const char* what() const throw();
private:
	std::string message;
	Loc loc;
};

class LLVMVisitor : public Visitor {
	//#include <visitorinclude>
public:
	LLVMVisitor();
	std::stack<llvm::Value*> valueStack;
	bool leaveAddExpression(AddExpression*) override;
	bool leaveAndAndExpression(AndAndExpression*) override; 
	bool leaveOrOrExpression(OrOrExpression*) override; 
	bool visitPostfixExpression(PostfixExpression*) override;
	bool visitPrimaryExpression(PrimaryExpression*) override;
	bool visitPrimativeExpression(PrimativeExpression*) override;

private:
	llvm::Module *module;
	llvm::IRBuilder<> builder;
};
