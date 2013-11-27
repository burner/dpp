#include <symboltablevisitor.hpp>
#include <unit.hpp>
#include <logger.hpp>

// generic

SymbolTableVisitor::SymbolTableVisitor() : 
		root(std::make_shared<SymbolTable>()) 
{
	this->stack.push(this->root);
}

void SymbolTableVisitor::newTableEntry() {
	auto t(std::make_shared<SymbolTable>(this->stack.top().get()));
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
		this->newTableEntry();
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
		fd->getDecl()->getIdentifier().getLocation()
	);
	this->blockStmt = true;
	this->giveAstNodeCurrentSymbolTable(fd);

	this->newTableEntry();
	
	return true; 
}

bool SymbolTableVisitor::leaveFunctionDecl(FunctionDecl*) { 
	return true;
}

bool SymbolTableVisitor::visitFunctionDecl(const FunctionDecl*) { 
	ASSERT_T_MSG(false, "SymbolTableVisitor::visitFunctionDecl(const Decl*)"
		 " not implemented. This is a non-const operation");
	return false;
}

bool SymbolTableVisitor::leaveBlockStatement(const BlockStatement*) { 
	ASSERT_T_MSG(false, "SymbolTableVisitor::leaveBlockStatement(const Decl*)"
		 " not implemented. This is a non-const operation");
	return false;
}

bool SymbolTableVisitor::visitBlockStatement(const BlockStatement*) { 
	ASSERT_T_MSG(false, "SymbolTableVisitor::visitBlockStatement(const Decl*)"
		 " not implemented. This is a non-const operation");
	return false;
}

bool SymbolTableVisitor::leaveFunctionDecl(const FunctionDecl*) { 
	ASSERT_T_MSG(false, "SymbolTableVisitor::leaveFunctionDecl(const Decl*)"
		 " not implemented. This is a non-const operation");
	return false;
}


// no modifications below

bool SymbolTableVisitor::visitOrOrExpression(OrOrExpression*) { return true; }
bool SymbolTableVisitor::visitOrOrExpression(const OrOrExpression*) { return true; }

bool SymbolTableVisitor::leaveOrOrExpression(OrOrExpression*) { return true; }
bool SymbolTableVisitor::leaveOrOrExpression(const OrOrExpression*) { return true; }
bool SymbolTableVisitor::visitAssignmentExpression(AssignmentExpression*) { return true; }
bool SymbolTableVisitor::visitAssignmentExpression(const AssignmentExpression*) { return true; }

bool SymbolTableVisitor::leaveAssignmentExpression(AssignmentExpression*) { return true; }
bool SymbolTableVisitor::leaveAssignmentExpression(const AssignmentExpression*) { return true; }
bool SymbolTableVisitor::visitVarDeclDirectInit(VarDeclDirectInit*) { return true; }
bool SymbolTableVisitor::visitVarDeclDirectInit(const VarDeclDirectInit*) { return true; }

bool SymbolTableVisitor::leaveVarDeclDirectInit(VarDeclDirectInit*) { return true; }
bool SymbolTableVisitor::leaveVarDeclDirectInit(const VarDeclDirectInit*) { return true; }
bool SymbolTableVisitor::visitConditionalExpression(ConditionalExpression*) { return true; }
bool SymbolTableVisitor::visitConditionalExpression(const ConditionalExpression*) { return true; }

bool SymbolTableVisitor::leaveConditionalExpression(ConditionalExpression*) { return true; }
bool SymbolTableVisitor::leaveConditionalExpression(const ConditionalExpression*) { return true; }
bool SymbolTableVisitor::visitConstDeclPrefix(ConstDeclPrefix*) { return true; }
bool SymbolTableVisitor::visitConstDeclPrefix(const ConstDeclPrefix*) { return true; }

bool SymbolTableVisitor::leaveConstDeclPrefix(ConstDeclPrefix*) { return true; }
bool SymbolTableVisitor::leaveConstDeclPrefix(const ConstDeclPrefix*) { return true; }
bool SymbolTableVisitor::visitVarDeclPrefix(VarDeclPrefix*) { return true; }
bool SymbolTableVisitor::visitVarDeclPrefix(const VarDeclPrefix*) { return true; }

bool SymbolTableVisitor::leaveVarDeclPrefix(VarDeclPrefix*) { return true; }
bool SymbolTableVisitor::leaveVarDeclPrefix(const VarDeclPrefix*) { return true; }
bool SymbolTableVisitor::visitVarDecl(VarDecl*) { return true; }
bool SymbolTableVisitor::visitVarDecl(const VarDecl*) { return true; }

bool SymbolTableVisitor::leaveVarDecl(VarDecl*) { return true; }
bool SymbolTableVisitor::leaveVarDecl(const VarDecl*) { return true; }
bool SymbolTableVisitor::visitExpression(Expression*) { return true; }
bool SymbolTableVisitor::visitExpression(const Expression*) { return true; }

bool SymbolTableVisitor::leaveExpression(Expression*) { return true; }
bool SymbolTableVisitor::leaveExpression(const Expression*) { return true; }
bool SymbolTableVisitor::visitArgument(Argument*) { return true; }
bool SymbolTableVisitor::visitArgument(const Argument*) { return true; }

bool SymbolTableVisitor::leaveArgument(Argument*) { return true; }
bool SymbolTableVisitor::leaveArgument(const Argument*) { return true; }
bool SymbolTableVisitor::visitStart(Start*) { return true; }
bool SymbolTableVisitor::visitStart(const Start*) { return true; }

bool SymbolTableVisitor::leaveStart(Start*) { return true; }
bool SymbolTableVisitor::leaveStart(const Start*) { return true; }
bool SymbolTableVisitor::visitTypeFollow(TypeFollow*) { return true; }
bool SymbolTableVisitor::visitTypeFollow(const TypeFollow*) { return true; }

bool SymbolTableVisitor::leaveTypeFollow(TypeFollow*) { return true; }
bool SymbolTableVisitor::leaveTypeFollow(const TypeFollow*) { return true; }
bool SymbolTableVisitor::visitFunctionPrototypeDecl(FunctionPrototypeDecl*) { return true; }
bool SymbolTableVisitor::visitFunctionPrototypeDecl(const FunctionPrototypeDecl*) { return true; }

bool SymbolTableVisitor::leaveFunctionPrototypeDecl(FunctionPrototypeDecl*) { return true; }
bool SymbolTableVisitor::leaveFunctionPrototypeDecl(const FunctionPrototypeDecl*) { return true; }
bool SymbolTableVisitor::visitIterationStatement(IterationStatement*) { return true; }
bool SymbolTableVisitor::visitIterationStatement(const IterationStatement*) { return true; }

bool SymbolTableVisitor::leaveIterationStatement(IterationStatement*) { return true; }
bool SymbolTableVisitor::leaveIterationStatement(const IterationStatement*) { return true; }
bool SymbolTableVisitor::visitType(Type*) { return true; }
bool SymbolTableVisitor::visitType(const Type*) { return true; }

bool SymbolTableVisitor::leaveType(Type*) { return true; }
bool SymbolTableVisitor::leaveType(const Type*) { return true; }
bool SymbolTableVisitor::visitPostfixExpression(PostfixExpression*) { return true; }
bool SymbolTableVisitor::visitPostfixExpression(const PostfixExpression*) { return true; }

bool SymbolTableVisitor::leavePostfixExpression(PostfixExpression*) { return true; }
bool SymbolTableVisitor::leavePostfixExpression(const PostfixExpression*) { return true; }
bool SymbolTableVisitor::visitAndAndExpression(AndAndExpression*) { return true; }
bool SymbolTableVisitor::visitAndAndExpression(const AndAndExpression*) { return true; }

bool SymbolTableVisitor::leaveAndAndExpression(AndAndExpression*) { return true; }
bool SymbolTableVisitor::leaveAndAndExpression(const AndAndExpression*) { return true; }
bool SymbolTableVisitor::visitVarDeclDeferedInit(VarDeclDeferedInit*) { return true; }
bool SymbolTableVisitor::visitVarDeclDeferedInit(const VarDeclDeferedInit*) { return true; }

bool SymbolTableVisitor::leaveVarDeclDeferedInit(VarDeclDeferedInit*) { return true; }
bool SymbolTableVisitor::leaveVarDeclDeferedInit(const VarDeclDeferedInit*) { return true; }
bool SymbolTableVisitor::visitStatement(Statement*) { return true; }
bool SymbolTableVisitor::visitStatement(const Statement*) { return true; }

bool SymbolTableVisitor::leaveStatement(Statement*) { return true; }
bool SymbolTableVisitor::leaveStatement(const Statement*) { return true; }
bool SymbolTableVisitor::visitBasicType(BasicType*) { return true; }
bool SymbolTableVisitor::visitBasicType(const BasicType*) { return true; }

bool SymbolTableVisitor::leaveBasicType(BasicType*) { return true; }
bool SymbolTableVisitor::leaveBasicType(const BasicType*) { return true; }
bool SymbolTableVisitor::visitExpressionStatement(ExpressionStatement*) { return true; }
bool SymbolTableVisitor::visitExpressionStatement(const ExpressionStatement*) { return true; }

bool SymbolTableVisitor::leaveExpressionStatement(ExpressionStatement*) { return true; }
bool SymbolTableVisitor::leaveExpressionStatement(const ExpressionStatement*) { return true; }
bool SymbolTableVisitor::visitArgumentList(ArgumentList*) { return true; }
bool SymbolTableVisitor::visitArgumentList(const ArgumentList*) { return true; }

bool SymbolTableVisitor::leaveArgumentList(ArgumentList*) { return true; }
bool SymbolTableVisitor::leaveArgumentList(const ArgumentList*) { return true; }
bool SymbolTableVisitor::visitStatementList(StatementList*) { return true; }
bool SymbolTableVisitor::visitStatementList(const StatementList*) { return true; }

bool SymbolTableVisitor::leaveStatementList(StatementList*) { return true; }
bool SymbolTableVisitor::leaveStatementList(const StatementList*) { return true; }
bool SymbolTableVisitor::visitOrExpression(OrExpression*) { return true; }
bool SymbolTableVisitor::visitOrExpression(const OrExpression*) { return true; }

bool SymbolTableVisitor::leaveOrExpression(OrExpression*) { return true; }
bool SymbolTableVisitor::leaveOrExpression(const OrExpression*) { return true; }
bool SymbolTableVisitor::visitXorExpression(XorExpression*) { return true; }
bool SymbolTableVisitor::visitXorExpression(const XorExpression*) { return true; }

bool SymbolTableVisitor::leaveXorExpression(XorExpression*) { return true; }
bool SymbolTableVisitor::leaveXorExpression(const XorExpression*) { return true; }
bool SymbolTableVisitor::visitAndExpression(AndExpression*) { return true; }
bool SymbolTableVisitor::visitAndExpression(const AndExpression*) { return true; }

bool SymbolTableVisitor::leaveAndExpression(AndExpression*) { return true; }
bool SymbolTableVisitor::leaveAndExpression(const AndExpression*) { return true; }
bool SymbolTableVisitor::visitEqualityExpression(EqualityExpression*) { return true; }
bool SymbolTableVisitor::visitEqualityExpression(const EqualityExpression*) { return true; }

bool SymbolTableVisitor::leaveEqualityExpression(EqualityExpression*) { return true; }
bool SymbolTableVisitor::leaveEqualityExpression(const EqualityExpression*) { return true; }
bool SymbolTableVisitor::visitRelExpression(RelExpression*) { return true; }
bool SymbolTableVisitor::visitRelExpression(const RelExpression*) { return true; }

bool SymbolTableVisitor::leaveRelExpression(RelExpression*) { return true; }
bool SymbolTableVisitor::leaveRelExpression(const RelExpression*) { return true; }
bool SymbolTableVisitor::visitShiftExpression(ShiftExpression*) { return true; }
bool SymbolTableVisitor::visitShiftExpression(const ShiftExpression*) { return true; }

bool SymbolTableVisitor::leaveShiftExpression(ShiftExpression*) { return true; }
bool SymbolTableVisitor::leaveShiftExpression(const ShiftExpression*) { return true; }
bool SymbolTableVisitor::visitAddExpression(AddExpression*) { return true; }
bool SymbolTableVisitor::visitAddExpression(const AddExpression*) { return true; }

bool SymbolTableVisitor::leaveAddExpression(AddExpression*) { return true; }
bool SymbolTableVisitor::leaveAddExpression(const AddExpression*) { return true; }
bool SymbolTableVisitor::visitMulExpression(MulExpression*) { return true; }
bool SymbolTableVisitor::visitMulExpression(const MulExpression*) { return true; }

bool SymbolTableVisitor::leaveMulExpression(MulExpression*) { return true; }
bool SymbolTableVisitor::leaveMulExpression(const MulExpression*) { return true; }
bool SymbolTableVisitor::visitCastExpression(CastExpression*) { return true; }
bool SymbolTableVisitor::visitCastExpression(const CastExpression*) { return true; }

bool SymbolTableVisitor::leaveCastExpression(CastExpression*) { return true; }
bool SymbolTableVisitor::leaveCastExpression(const CastExpression*) { return true; }
bool SymbolTableVisitor::visitUnaryExpression(UnaryExpression*) { return true; }
bool SymbolTableVisitor::visitUnaryExpression(const UnaryExpression*) { return true; }

bool SymbolTableVisitor::leaveUnaryExpression(UnaryExpression*) { return true; }
bool SymbolTableVisitor::leaveUnaryExpression(const UnaryExpression*) { return true; }
bool SymbolTableVisitor::visitPostfixNextExpression(PostfixNextExpression*) { return true; }
bool SymbolTableVisitor::visitPostfixNextExpression(const PostfixNextExpression*) { return true; }

bool SymbolTableVisitor::leavePostfixNextExpression(PostfixNextExpression*) { return true; }
bool SymbolTableVisitor::leavePostfixNextExpression(const PostfixNextExpression*) { return true; }
bool SymbolTableVisitor::visitPrimaryExpression(PrimaryExpression*) { return true; }
bool SymbolTableVisitor::visitPrimaryExpression(const PrimaryExpression*) { return true; }

bool SymbolTableVisitor::leavePrimaryExpression(PrimaryExpression*) { return true; }
bool SymbolTableVisitor::leavePrimaryExpression(const PrimaryExpression*) { return true; }

bool SymbolTableVisitor::visitDecl(Decl*) {
	ASSERT_T_MSG(false, "SymbolTableVisitor::visitDecl(Decl*) not implemented");
	return false;
}

bool SymbolTableVisitor::visitDecl(const Decl*) {
	ASSERT_T_MSG(false, "SymbolTableVisitor::visitDecl(const Decl*) not implemented");
	return false;
}

bool SymbolTableVisitor::leaveDecl(Decl*) {
	ASSERT_T_MSG(false, "SymbolTableVisitor::leaveDecl(Decl*) not implemented");
	return false;
}

bool SymbolTableVisitor::leaveDecl(const Decl*) {
	ASSERT_T_MSG(false, "SymbolTableVisitor::leaveDecl(const Decl*) not implemented");
	return false;
}
