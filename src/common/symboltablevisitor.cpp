#include <symboltablevisitor.hpp>
#include <unit.hpp>
#include <logger.hpp>

// generic

SymbolTableVisitor::SymbolTableVisitor() : 
		root(std::make_shared<SymbolTable>()) 
{
	this->stack.push(this->root);
}

void SymbolTableVisitor::newTable(SymbolTableType type) {
	auto t(std::make_shared<SymbolTable>(this->stack.top().get(), type));
	this->stack.top()->insertNewTable(t);
	this->stack.push(t);
}

void SymbolTableVisitor::giveAstNodeCurrentSymbolTable(AstNode* node) {
	node->setSymbolTable(this->stack.top().get());
}

SymbolTablePtr SymbolTableVisitor::getRoot() {
	return this->root;
}

SymbolTableConstPtr SymbolTableVisitor::getRoot() const {
	return this->root;
}

// visitor and leaver

bool SymbolTableVisitor::visitBlockStatement(BlockStatement* block) { 
	if(!this->blockStmt) {
		this->newTable();
	}

	this->giveAstNodeCurrentSymbolTable(block);
	this->blockStmt = false;
	return true;
}

bool SymbolTableVisitor::leaveBlockStatement(BlockStatement*) { 
	this->stack.pop();
	return true;
}

bool SymbolTableVisitor::visitFunctionDecl(FunctionDecl* fd) { 
	this->stack.top()->insert(
		fd->getDecl()->getIdentifier().value.stringValue,
		SymbolTableEntryType::Function,
		fd->getDecl()->getIdentifier().getLocation()
	);
	this->blockStmt = true;
	this->giveAstNodeCurrentSymbolTable(fd);

	this->newTable();
	
	return true; 
}

bool SymbolTableVisitor::visitOrOrExpression(OrOrExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitAssignmentExpression(AssignmentExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitConditionalExpression(ConditionalExpression* node)
{
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitConstDeclPrefix(ConstDeclPrefix* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	this->stack.top()->insert(node->getIdentifier().value.stringValue,
		SymbolTableEntryType::Constant, node->getIdentifier().getLocation()
	);
	return true;
}

bool SymbolTableVisitor::visitVarDeclPrefix(VarDeclPrefix* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	this->stack.top()->insert(node->getIdentifier().value.stringValue,
		SymbolTableEntryType::Variable, node->getIdentifier().getLocation()
	);
	return true;
}

bool SymbolTableVisitor::visitVarDecl(VarDecl* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitExpression(Expression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitArgument(Argument* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitStart(Start* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitTypeFollow(TypeFollow* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitType(Type* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitAndAndExpression(AndAndExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitVarDeclDirectInit(VarDeclDirectInit* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitStatement(Statement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitBasicType(BasicType* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitExpressionStatement(ExpressionStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitFunctionPrototypeDecl(
		FunctionPrototypeDecl* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitPostfixExpression(PostfixExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitArgumentList(ArgumentList* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitStatementList(StatementList* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitOrExpression(OrExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitXorExpression(XorExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitAndExpression(AndExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitEqualityExpression(EqualityExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitRelExpression(RelExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitShiftExpression(ShiftExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitAddExpression(AddExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitMulExpression(MulExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitCastExpression(CastExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitUnaryExpression(UnaryExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitPostfixNextExpression(
		PostfixNextExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitPrimaryExpression(PrimaryExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitDecl(Decl* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitReturnStatement(ReturnStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitBranchStatement(BranchStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitIfStatement(IfStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitIfFollowStatement(IfFollowStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitPrimativeExpression(PrimativeExpression* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitContinueExpression(ContinueStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitBreakStatement(BreakStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitForStatement(ForStatement* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitUnnamedArgList(UnnamedArgList* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitUnnamedArg(UnnamedArg* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitTypeDelFun(TypeDelFun* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitTypeFollows(TypeFollows* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitInitLists(InitLists* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}

bool SymbolTableVisitor::visitModifier(Modifier* node) {
	this->giveAstNodeCurrentSymbolTable(node);
	return true;
}
