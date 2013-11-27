// DO not MODIFY this FILE it IS generated

#pragma once

#include <stack>

#include <symboltable.hpp>
#include <visitor.hpp>

typedef std::stack<SymbolTablePtr> SymbolTableStack;

class SymbolTableVisitor : public Visitor {
public:
	SymbolTableVisitor();
	void newTableEntry();

	// All visit and leave prototies
	#include <visitorinclude>

private:
	SymbolTablePtr root;
	SymbolTableStack stack;
};
