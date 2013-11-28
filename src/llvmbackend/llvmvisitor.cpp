#include <ast.hpp>
#include <llvmvisitor.hpp>

#include <unit.hpp>

LLVMVisitor::LLVMVisitor() : 
		module(new llvm::Module("main", llvm::getGlobalContext())) 
{

}

bool LLVMVisitor::visitOrOrExpression(OrOrExpression*) { return true; }
bool LLVMVisitor::visitOrOrExpression(const OrOrExpression*) { return true; }

bool LLVMVisitor::leaveOrOrExpression(OrOrExpression*) { return true; }
bool LLVMVisitor::leaveOrOrExpression(const OrOrExpression*) { return true; }
bool LLVMVisitor::visitAssignmentExpression(AssignmentExpression*) { return true; }
bool LLVMVisitor::visitAssignmentExpression(const AssignmentExpression*) { return true; }

bool LLVMVisitor::leaveAssignmentExpression(AssignmentExpression*) { return true; }
bool LLVMVisitor::leaveAssignmentExpression(const AssignmentExpression*) { return true; }
bool LLVMVisitor::visitVarDeclDirectInit(VarDeclDirectInit*) { return true; }
bool LLVMVisitor::visitVarDeclDirectInit(const VarDeclDirectInit*) { return true; }

bool LLVMVisitor::leaveVarDeclDirectInit(VarDeclDirectInit*) { return true; }
bool LLVMVisitor::leaveVarDeclDirectInit(const VarDeclDirectInit*) { return true; }
bool LLVMVisitor::visitConditionalExpression(ConditionalExpression*) { return true; }
bool LLVMVisitor::visitConditionalExpression(const ConditionalExpression*) { return true; }

bool LLVMVisitor::leaveConditionalExpression(ConditionalExpression*) { return true; }
bool LLVMVisitor::leaveConditionalExpression(const ConditionalExpression*) { return true; }
bool LLVMVisitor::visitConstDeclPrefix(ConstDeclPrefix*) { return true; }
bool LLVMVisitor::visitConstDeclPrefix(const ConstDeclPrefix*) { return true; }

bool LLVMVisitor::leaveConstDeclPrefix(ConstDeclPrefix*) { return true; }
bool LLVMVisitor::leaveConstDeclPrefix(const ConstDeclPrefix*) { return true; }
bool LLVMVisitor::visitVarDeclPrefix(VarDeclPrefix*) { return true; }
bool LLVMVisitor::visitVarDeclPrefix(const VarDeclPrefix*) { return true; }

bool LLVMVisitor::leaveVarDeclPrefix(VarDeclPrefix*) { return true; }
bool LLVMVisitor::leaveVarDeclPrefix(const VarDeclPrefix*) { return true; }
bool LLVMVisitor::visitVarDecl(VarDecl*) { return true; }
bool LLVMVisitor::visitVarDecl(const VarDecl*) { return true; }

bool LLVMVisitor::leaveVarDecl(VarDecl*) { return true; }
bool LLVMVisitor::leaveVarDecl(const VarDecl*) { return true; }
bool LLVMVisitor::visitExpression(Expression*) { return true; }
bool LLVMVisitor::visitExpression(const Expression*) { return true; }

bool LLVMVisitor::leaveExpression(Expression*) { return true; }
bool LLVMVisitor::leaveExpression(const Expression*) { return true; }
bool LLVMVisitor::visitArgument(Argument*) { return true; }
bool LLVMVisitor::visitArgument(const Argument*) { return true; }

bool LLVMVisitor::leaveArgument(Argument*) { return true; }
bool LLVMVisitor::leaveArgument(const Argument*) { return true; }
bool LLVMVisitor::visitStart(Start*) { return true; }
bool LLVMVisitor::visitStart(const Start*) { return true; }

bool LLVMVisitor::leaveStart(Start*) { return true; }
bool LLVMVisitor::leaveStart(const Start*) { return true; }
bool LLVMVisitor::visitTypeFollow(TypeFollow*) { return true; }
bool LLVMVisitor::visitTypeFollow(const TypeFollow*) { return true; }

bool LLVMVisitor::leaveTypeFollow(TypeFollow*) { return true; }
bool LLVMVisitor::leaveTypeFollow(const TypeFollow*) { return true; }
bool LLVMVisitor::visitBlockStatement(BlockStatement*) { return true; }
bool LLVMVisitor::visitBlockStatement(const BlockStatement*) { return true; }

bool LLVMVisitor::leaveBlockStatement(BlockStatement*) { return true; }
bool LLVMVisitor::leaveBlockStatement(const BlockStatement*) { return true; }
bool LLVMVisitor::visitFunctionPrototypeDecl(FunctionPrototypeDecl*) { return true; }
bool LLVMVisitor::visitFunctionPrototypeDecl(const FunctionPrototypeDecl*) { return true; }

bool LLVMVisitor::leaveFunctionPrototypeDecl(FunctionPrototypeDecl*) { return true; }
bool LLVMVisitor::leaveFunctionPrototypeDecl(const FunctionPrototypeDecl*) { return true; }
bool LLVMVisitor::visitIterationStatement(IterationStatement*) { return true; }
bool LLVMVisitor::visitIterationStatement(const IterationStatement*) { return true; }

bool LLVMVisitor::leaveIterationStatement(IterationStatement*) { return true; }
bool LLVMVisitor::leaveIterationStatement(const IterationStatement*) { return true; }
bool LLVMVisitor::visitType(Type*) { return true; }
bool LLVMVisitor::visitType(const Type*) { return true; }

bool LLVMVisitor::leaveType(Type*) { return true; }
bool LLVMVisitor::leaveType(const Type*) { return true; }
bool LLVMVisitor::visitPostfixExpression(PostfixExpression*) { return true; }
bool LLVMVisitor::visitPostfixExpression(const PostfixExpression*) { return true; }

bool LLVMVisitor::leavePostfixExpression(PostfixExpression*) { return true; }
bool LLVMVisitor::leavePostfixExpression(const PostfixExpression*) { return true; }
bool LLVMVisitor::visitFunctionDecl(FunctionDecl*) { return true; }
bool LLVMVisitor::visitFunctionDecl(const FunctionDecl*) { return true; }

bool LLVMVisitor::leaveFunctionDecl(FunctionDecl*) { return true; }
bool LLVMVisitor::leaveFunctionDecl(const FunctionDecl*) { return true; }
bool LLVMVisitor::visitAndAndExpression(AndAndExpression*) { return true; }
bool LLVMVisitor::visitAndAndExpression(const AndAndExpression*) { return true; }

bool LLVMVisitor::leaveAndAndExpression(AndAndExpression*) { return true; }
bool LLVMVisitor::leaveAndAndExpression(const AndAndExpression*) { return true; }
bool LLVMVisitor::visitVarDeclDeferedInit(VarDeclDeferedInit*) { return true; }
bool LLVMVisitor::visitVarDeclDeferedInit(const VarDeclDeferedInit*) { return true; }

bool LLVMVisitor::leaveVarDeclDeferedInit(VarDeclDeferedInit*) { return true; }
bool LLVMVisitor::leaveVarDeclDeferedInit(const VarDeclDeferedInit*) { return true; }
bool LLVMVisitor::visitStatement(Statement*) { return true; }
bool LLVMVisitor::visitStatement(const Statement*) { return true; }

bool LLVMVisitor::leaveStatement(Statement*) { return true; }
bool LLVMVisitor::leaveStatement(const Statement*) { return true; }
bool LLVMVisitor::visitBasicType(BasicType*) { return true; }
bool LLVMVisitor::visitBasicType(const BasicType*) { return true; }

bool LLVMVisitor::leaveBasicType(BasicType*) { return true; }
bool LLVMVisitor::leaveBasicType(const BasicType*) { return true; }
bool LLVMVisitor::visitExpressionStatement(ExpressionStatement*) { return true; }
bool LLVMVisitor::visitExpressionStatement(const ExpressionStatement*) { return true; }

bool LLVMVisitor::leaveExpressionStatement(ExpressionStatement*) { return true; }
bool LLVMVisitor::leaveExpressionStatement(const ExpressionStatement*) { return true; }
bool LLVMVisitor::visitArgumentList(ArgumentList*) { return true; }
bool LLVMVisitor::visitArgumentList(const ArgumentList*) { return true; }

bool LLVMVisitor::leaveArgumentList(ArgumentList*) { return true; }
bool LLVMVisitor::leaveArgumentList(const ArgumentList*) { return true; }
bool LLVMVisitor::visitStatementList(StatementList*) { return true; }
bool LLVMVisitor::visitStatementList(const StatementList*) { return true; }

bool LLVMVisitor::leaveStatementList(StatementList*) { return true; }
bool LLVMVisitor::leaveStatementList(const StatementList*) { return true; }
bool LLVMVisitor::visitOrExpression(OrExpression*) { return true; }
bool LLVMVisitor::visitOrExpression(const OrExpression*) { return true; }

bool LLVMVisitor::leaveOrExpression(OrExpression*) { return true; }
bool LLVMVisitor::leaveOrExpression(const OrExpression*) { return true; }
bool LLVMVisitor::visitXorExpression(XorExpression*) { return true; }
bool LLVMVisitor::visitXorExpression(const XorExpression*) { return true; }

bool LLVMVisitor::leaveXorExpression(XorExpression*) { return true; }
bool LLVMVisitor::leaveXorExpression(const XorExpression*) { return true; }
bool LLVMVisitor::visitAndExpression(AndExpression*) { return true; }
bool LLVMVisitor::visitAndExpression(const AndExpression*) { return true; }

bool LLVMVisitor::leaveAndExpression(AndExpression*) { return true; }
bool LLVMVisitor::leaveAndExpression(const AndExpression*) { return true; }
bool LLVMVisitor::visitEqualityExpression(EqualityExpression*) { return true; }
bool LLVMVisitor::visitEqualityExpression(const EqualityExpression*) { return true; }

bool LLVMVisitor::leaveEqualityExpression(EqualityExpression*) { return true; }
bool LLVMVisitor::leaveEqualityExpression(const EqualityExpression*) { return true; }
bool LLVMVisitor::visitRelExpression(RelExpression*) { return true; }
bool LLVMVisitor::visitRelExpression(const RelExpression*) { return true; }

bool LLVMVisitor::leaveRelExpression(RelExpression*) { return true; }
bool LLVMVisitor::leaveRelExpression(const RelExpression*) { return true; }
bool LLVMVisitor::visitShiftExpression(ShiftExpression*) { return true; }
bool LLVMVisitor::visitShiftExpression(const ShiftExpression*) { return true; }

bool LLVMVisitor::leaveShiftExpression(ShiftExpression*) { return true; }
bool LLVMVisitor::leaveShiftExpression(const ShiftExpression*) { return true; }
bool LLVMVisitor::visitAddExpression(AddExpression*) { return true; }
bool LLVMVisitor::visitAddExpression(const AddExpression*) { return true; }

bool LLVMVisitor::leaveAddExpression(AddExpression*) { return true; }
bool LLVMVisitor::leaveAddExpression(const AddExpression*) { return true; }
bool LLVMVisitor::visitMulExpression(MulExpression*) { return true; }
bool LLVMVisitor::visitMulExpression(const MulExpression*) { return true; }

bool LLVMVisitor::leaveMulExpression(MulExpression*) { return true; }
bool LLVMVisitor::leaveMulExpression(const MulExpression*) { return true; }
bool LLVMVisitor::visitCastExpression(CastExpression*) { return true; }
bool LLVMVisitor::visitCastExpression(const CastExpression*) { return true; }

bool LLVMVisitor::leaveCastExpression(CastExpression*) { return true; }
bool LLVMVisitor::leaveCastExpression(const CastExpression*) { return true; }
bool LLVMVisitor::visitUnaryExpression(UnaryExpression*) { return true; }
bool LLVMVisitor::visitUnaryExpression(const UnaryExpression*) { return true; }

bool LLVMVisitor::leaveUnaryExpression(UnaryExpression*) { return true; }
bool LLVMVisitor::leaveUnaryExpression(const UnaryExpression*) { return true; }
bool LLVMVisitor::visitPostfixNextExpression(PostfixNextExpression*) { return true; }
bool LLVMVisitor::visitPostfixNextExpression(const PostfixNextExpression*) { return true; }

bool LLVMVisitor::leavePostfixNextExpression(PostfixNextExpression*) { return true; }
bool LLVMVisitor::leavePostfixNextExpression(const PostfixNextExpression*) { return true; }
bool LLVMVisitor::visitPrimaryExpression(PrimaryExpression*) { return true; }
bool LLVMVisitor::visitPrimaryExpression(const PrimaryExpression*) { return true; }

bool LLVMVisitor::leavePrimaryExpression(PrimaryExpression*) { return true; }
bool LLVMVisitor::leavePrimaryExpression(const PrimaryExpression*) { return true; }
bool LLVMVisitor::visitReturnStatement(ReturnStatement*) { return true; }
bool LLVMVisitor::visitReturnStatement(const ReturnStatement*) { return true; }

bool LLVMVisitor::leaveReturnStatement(ReturnStatement*) { return true; }
bool LLVMVisitor::leaveReturnStatement(const ReturnStatement*) { return true; }

bool LLVMVisitor::visitBranchStatement(BranchStatement*) { return true; }
bool LLVMVisitor::visitBranchStatement(const BranchStatement*) { return true; }

bool LLVMVisitor::leaveBranchStatement(BranchStatement*) { return true; }
bool LLVMVisitor::leaveBranchStatement(const BranchStatement*) { return true; }

bool LLVMVisitor::visitDecl(Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::visitDecl(Decl*) not implemented");
	return false;
}

bool LLVMVisitor::visitDecl(const Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::visitDecl(const Decl*) not implemented");
	return false;
}

bool LLVMVisitor::leaveDecl(Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::leaveDecl(Decl*) not implemented");
	return false;
}

bool LLVMVisitor::leaveDecl(const Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::leaveDecl(const Decl*) not implemented");
	return false;
}
