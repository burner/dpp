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
	virtual bool visitBlockStatement(BlockStatement*);
	virtual bool leaveBlockStatement(BlockStatement*);
	virtual bool visitFunctionDecl(FunctionDecl*);
	virtual bool visitAssignmentExpression(AssignmentExpression*);
	virtual bool visitVarDeclDirectInit(VarDeclDirectInit*);
	virtual bool visitConditionalExpression(ConditionalExpression*);
	virtual bool visitConstDeclPrefix(ConstDeclPrefix*);
	virtual bool visitOrOrExpression(OrOrExpression*);
	virtual bool visitVarDeclPrefix(VarDeclPrefix*);
	virtual bool visitVarDecl(VarDecl*);
	virtual bool visitExpression(Expression*);
	virtual bool visitArgument(Argument*);
	virtual bool visitStart(Start*);
	virtual bool visitTypeFollow(TypeFollow*);
	virtual bool visitType(Type*);
	virtual bool visitAndAndExpression(AndAndExpression*);
	virtual bool visitStatement(Statement*);
	virtual bool visitBasicType(BasicType*);
	virtual bool visitExpressionStatement(ExpressionStatement*);
	virtual bool visitFunctionPrototypeDecl(FunctionPrototypeDecl*);
	virtual bool visitPostfixExpression(PostfixExpression*);
	virtual bool visitArgumentList(ArgumentList*);
	virtual bool visitStatementList(StatementList*);
	virtual bool visitOrExpression(OrExpression*);
	virtual bool visitXorExpression(XorExpression*);
	virtual bool visitAndExpression(AndExpression*);
	virtual bool visitEqualityExpression(EqualityExpression*);
	virtual bool visitRelExpression(RelExpression*);
	virtual bool visitShiftExpression(ShiftExpression*);
	virtual bool visitAddExpression(AddExpression*);
	virtual bool visitMulExpression(MulExpression*);
	virtual bool visitCastExpression(CastExpression*);
	virtual bool visitUnaryExpression(UnaryExpression*);
	virtual bool visitPostfixNextExpression(PostfixNextExpression*);
	virtual bool visitPrimaryExpression(PrimaryExpression*);
	virtual bool visitDecl(Decl*);
	virtual bool visitReturnStatement(ReturnStatement*);
	virtual bool visitBranchStatement(BranchStatement*);
	virtual bool visitIfStatement(IfStatement*);
	virtual bool visitIfFollowStatement(IfFollowStatement*);
	virtual bool visitPrimativeExpression(PrimativeExpression*);
	virtual bool visitContinueExpression(ContinueStatement*);
	virtual bool visitBreakStatement(BreakStatement*);
	virtual bool visitForStatement(ForStatement*);
	virtual bool visitUnnamedArgList(UnnamedArgList*);
	virtual bool visitUnnamedArg(UnnamedArg*);
	virtual bool visitTypeDelFun(TypeDelFun*);
	virtual bool visitTypeFollows(TypeFollows*);
	virtual bool visitInitLists(InitLists*);
	virtual bool visitModifier(Modifier*);

private:
	SymbolTableStack stack;

	// if we find a "def" don't open a new symboltable on the next opening
	// block statement
	bool blockStmt = false;

	void giveAstNodeCurrentSymbolTable(AstNode*);

	SymbolTablePtr root;
};
