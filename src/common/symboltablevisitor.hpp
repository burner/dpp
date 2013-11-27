#pragma once

#include <stack>

#include <symboltable.hpp>
#include <visitor.hpp>

typedef std::stack<SymbolTablePtr> SymbolTableStack;

class SymbolTableVisitor : public Visitor {
public:
	SymbolTableVisitor();
	void newTableEntry();

	SymbolTablePtr getRoot();
	SymbolTableConstPtr getRoot() const;

	// All visit and leave prototies
	#include <visitorinclude>

private:
	SymbolTableStack stack;

	// if we find a "def" don't open a new symboltable on the next opening
	// block statement
	bool blockStmt = false;

	void giveAstNodeCurrentSymbolTable(AstNode*);

	SymbolTablePtr root;
};
