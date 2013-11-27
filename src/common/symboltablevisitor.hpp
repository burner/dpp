#pragma once

#include <stack>

#include <symboltable.hpp>
#include <visitor.hpp>

typedef std::stack<SymbolTablePtr> SymbolTableStack;

class SymbolTableVisitor : public Visitor {
public:
	explicit SymbolTableVisitor();
	void newTable(SymbolTableType type = SymbolTableType::Ordered);

	SymbolTablePtr getRoot();
	SymbolTableConstPtr getRoot() const;

	// All visit and leave prototies
	//#include <visitorinclude>
	bool visitBlockStatement(BlockStatement*);
	bool leaveBlockStatement(BlockStatement*);
	bool visitFunctionDecl(FunctionDecl*);
	bool visitAssignmentExpression(AssignmentExpression*);
	bool visitVarDeclDirectInit(VarDeclDirectInit*);
	bool visitConditionalExpression(ConditionalExpression*);
	bool visitConstDeclPrefix(ConstDeclPrefix*);
	bool visitOrOrExpression(OrOrExpression*);
	bool visitVarDeclPrefix(VarDeclPrefix*);
	bool visitVarDecl(VarDecl*);
	bool visitExpression(Expression*);
	bool visitArgument(Argument*);
	bool visitStart(Start*);
	bool visitTypeFollow(TypeFollow*);
	bool visitIterationStatement(IterationStatement*);
	bool visitType(Type*);
	bool visitAndAndExpression(AndAndExpression*);
	bool visitVarDeclDeferedInit(VarDeclDeferedInit*);
	bool visitStatement(Statement*);
	bool visitBasicType(BasicType*);
	bool visitExpressionStatement(ExpressionStatement*);
	bool visitFunctionPrototypeDecl(FunctionPrototypeDecl*);
	bool visitPostfixExpression(PostfixExpression*);
	bool visitArgumentList(ArgumentList*);
	bool visitStatementList(StatementList*);
	bool visitOrExpression(OrExpression*);
	bool visitXorExpression(XorExpression*);
	bool visitAndExpression(AndExpression*);
	bool visitEqualityExpression(EqualityExpression*);
	bool visitRelExpression(RelExpression*);
	bool visitShiftExpression(ShiftExpression*);
	bool visitAddExpression(AddExpression*);
	bool visitMulExpression(MulExpression*);
	bool visitCastExpression(CastExpression*);
	bool visitUnaryExpression(UnaryExpression*);
	bool visitPostfixNextExpression(PostfixNextExpression*);
	bool visitPrimaryExpression(PrimaryExpression*);
	bool visitDecl(Decl*);

private:
	SymbolTableStack stack;

	// if we find a "def" don't open a new symboltable on the next opening
	// block statement
	bool blockStmt = false;

	void giveAstNodeCurrentSymbolTable(AstNode*);

	SymbolTablePtr root;
};
