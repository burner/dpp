#include <ast.hpp>
#include <llvmvisitor.hpp>

#include <format.hpp>
#include <unit.hpp>
#include <logger.hpp>

#define LLVMDump(v) llvmDumpImpl(v, __LINE__, __FILE__)

inline std::string shortenString(const std::string& str) {
	size_t idx = str.rfind('/');
	if(idx == std::string::npos) {
		return str;
	} else {
		return str.substr(idx+1);
	}
}

template<typename T>
void llvmDumpImpl(T t, int line, const char* file) {
	format(std::cout, "%s:%u ", shortenString(file), line);
	llvm::raw_os_ostream sstream(std::cout);
	sstream<<(*t);
	std::cout<<std::endl;
}

LLVMVisitorException::LLVMVisitorException(const std::string& m, Loc l) :
		message(m), loc(l)
{
}

const char* LLVMVisitorException::what() const throw() {
	return format("msg '%s' loc '%s'", this->message, this->loc.toString()).
		c_str();
}

LLVMVisitor::LLVMVisitor() : 
		module(new llvm::Module("main", llvm::getGlobalContext())),
		builder(llvm::getGlobalContext())
{

}

bool LLVMVisitor::visitPrimativeExpression(PrimativeExpression* prim) { 
	LOG("%s", prim->getRule());
	switch(prim->getRule()) {
	case PrimativeExpressionEnum::ByteValue:
		this->valueStack.push(
			llvm::ConstantInt::get(
				llvm::Type::getInt8Ty(llvm::getGlobalContext()
			),
			prim->getValue().value.charValue
		));
		return true;
	case PrimativeExpressionEnum::DoubleValue:
		this->valueStack.push(
			llvm::ConstantFP::get(
				llvm::Type::getDoubleTy(llvm::getGlobalContext()
			),
			prim->getValue().value.doubleValue
		));
		return true;
	case PrimativeExpressionEnum::False:
		this->valueStack.push(
			llvm::ConstantInt::get(
				llvm::Type::getInt1Ty(llvm::getGlobalContext()
			), false
		));
		return true;
	case PrimativeExpressionEnum::FloatValue:
		this->valueStack.push(
			llvm::ConstantFP::get(
				llvm::Type::getFloatTy(llvm::getGlobalContext()
			),
			prim->getValue().value.floatValue
		));
		return true;
	case PrimativeExpressionEnum::IntValue:
		this->valueStack.push(
			llvm::ConstantInt::get(
				llvm::Type::getInt32Ty(llvm::getGlobalContext()
			),
			prim->getValue().value.intValue
		));
		return true;
	case PrimativeExpressionEnum::LongValue:
		this->valueStack.push(
			llvm::ConstantInt::get(
				llvm::Type::getInt64Ty(llvm::getGlobalContext()
			),
			prim->getValue().value.intValue
		));
		return true;
	case PrimativeExpressionEnum::RealValue:
		this->valueStack.push(
			llvm::ConstantFP::get(
				llvm::Type::getX86_FP80Ty(llvm::getGlobalContext()
			),
			prim->getValue().value.longDoubleValue
		));
		return true;
	case PrimativeExpressionEnum::ShortValue:
		this->valueStack.push(
			llvm::ConstantInt::get(
				llvm::Type::getInt16Ty(llvm::getGlobalContext()
			),
			prim->getValue().value.shortValue
		));
		return true;
	case PrimativeExpressionEnum::StringValue:
		break;
	case PrimativeExpressionEnum::True:
		this->valueStack.push(
			llvm::ConstantInt::get(
				llvm::Type::getInt1Ty(llvm::getGlobalContext()
			), true
		));
		return true;
	case PrimativeExpressionEnum::UByteValue:
		break;
	case PrimativeExpressionEnum::UIntValue:
		break;
	case PrimativeExpressionEnum::ULongValue:
		break;
	case PrimativeExpressionEnum::UShortValue:
		break;
	default:
		break;
	}
	throw LLVMVisitorException(
		format("PrimativeExpression Rule('%d') not implemented",
			prim->getRule()
		), prim->getValue().getLocation()
	);
	return true; 
}

bool LLVMVisitor::visitPrimaryExpression(PrimaryExpression*) { 
	return true; 
}

bool LLVMVisitor::visitPostfixExpression(PostfixExpression*) {
   	return true; 
}

bool LLVMVisitor::leaveOrOrExpression(OrOrExpression* expr) { 
	if(expr->getRule() == OrOrExpressionEnum::LogicalOr) {
		ASSERT_T_MSG(this->valueStack.size() >= 2u, 
			format("%u stackSize(%u)", expr->getId(), this->valueStack.size())
		);

		auto lhs = this->valueStack.top();
		this->valueStack.pop();
		auto rhs = this->valueStack.top();
		this->valueStack.pop();

		this->valueStack.push(
			this->builder.CreateOr(lhs, rhs, "LogicalOr")
		);

		LLVMDump(this->valueStack.top());
	}
	return true; 
}

bool LLVMVisitor::leaveAndAndExpression(AndAndExpression* expr) { 
	if(expr->getRule() == AndAndExpressionEnum::LogicalAnd) {
		ASSERT_T_MSG(this->valueStack.size() >= 2u, 
			format("%u stackSize(%u)", expr->getId(), this->valueStack.size())
		);

		auto rhs = this->valueStack.top();
		this->valueStack.pop();
		auto lhs = this->valueStack.top();
		this->valueStack.pop();

		this->valueStack.push(
			this->builder.CreateAnd(lhs, rhs, "LogicalOr")
		);

		LLVMDump(this->valueStack.top());
	}
	return true; 
}

bool LLVMVisitor::leaveAddExpression(AddExpression* expr) {
	if(expr->getRule() == AddExpressionEnum::Plus
			|| expr->getRule() == AddExpressionEnum::Minus)
	{
		ASSERT_T_MSG(this->valueStack.size() >= 2u, 
			format("%u stackSize(%u)", expr->getId(), this->valueStack.size())
		);

		auto rhs = this->valueStack.top();
		auto rhsType = rhs->getType();
		this->valueStack.pop();
		auto lhs = this->valueStack.top();
		auto lhsType = lhs->getType();
		this->valueStack.pop();
		LLVMDump(lhs);
		LLVMDump(rhs);

		ASSERT_EQ(valueStack.size(), 0);
		if(rhsType->isIntegerTy() && rhsType->isIntegerTy()) {
			if(rhsType->getIntegerBitWidth() == lhsType->getIntegerBitWidth()) {
				this->valueStack.push(
					expr->getRule() == AddExpressionEnum::Plus ?
						this->builder.CreateAdd(lhs, rhs, "Add") :
						this->builder.CreateSub(lhs, rhs, "Sub")
				);
			} else {
				throw LLVMVisitorException(format("%s operation"
					" between Integers of different size lhs(%u) rhs(%u)",
					expr->getRule() == AddExpressionEnum::Plus ? "Add" : 
					"Minus", lhsType->getIntegerBitWidth(),
					rhsType->getIntegerBitWidth()), Loc());
			}
		}
		if((rhsType->isFloatTy() || rhsType->isDoubleTy() ||
				rhsType->isX86_FP80Ty()) && 
				rhsType->getTypeID() == lhsType->getTypeID()) {
			this->valueStack.push(
				expr->getRule() == AddExpressionEnum::Plus ?
					this->builder.CreateFAdd(lhs, rhs, "Add") :
					this->builder.CreateFSub(lhs, rhs, "Sub")
			);
		} else {
			throw LLVMVisitorException(format("%s operation"
				" between different float types of different size "
				"lhs(%u) rhs(%u)",
				expr->getRule() == AddExpressionEnum::Plus ? "Add" : 
				"Minus", lhsType->getTypeID(),
				rhsType->getTypeID()), Loc());
		}
		
		ASSERT_EQ(valueStack.size(), 1);

		LLVMDump(this->valueStack.top());
	}
	return true;
}

//
// empty
//

bool LLVMVisitor::visitOrOrExpression(OrOrExpression*) { return true; }

bool LLVMVisitor::visitOrOrExpression(const OrOrExpression*) { return true; }

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
bool LLVMVisitor::visitType(Type*) { return true; }
bool LLVMVisitor::visitType(const Type*) { return true; }

bool LLVMVisitor::leaveType(Type*) { return true; }
bool LLVMVisitor::leaveType(const Type*) { return true; }
bool LLVMVisitor::visitPostfixExpression(const PostfixExpression*) { return true; }

bool LLVMVisitor::leavePostfixExpression(PostfixExpression*) { return true; }
bool LLVMVisitor::leavePostfixExpression(const PostfixExpression*) { return true; }
bool LLVMVisitor::visitFunctionDecl(FunctionDecl*) { return true; }
bool LLVMVisitor::visitFunctionDecl(const FunctionDecl*) { return true; }

bool LLVMVisitor::leaveFunctionDecl(FunctionDecl*) { return true; }
bool LLVMVisitor::leaveFunctionDecl(const FunctionDecl*) { return true; }
bool LLVMVisitor::visitAndAndExpression(AndAndExpression*) { return true; }
bool LLVMVisitor::visitAndAndExpression(const AndAndExpression*) { return true; }

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
bool LLVMVisitor::visitAddExpression(const AddExpression*) { return true; }

bool LLVMVisitor::visitAddExpression(AddExpression*) { return true; }
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

bool LLVMVisitor::visitForStatement(ForStatement*) { return true; }
bool LLVMVisitor::visitForStatement(const ForStatement*) { return true; }

bool LLVMVisitor::leaveForStatement(ForStatement*) { return true; }
bool LLVMVisitor::leaveForStatement(const ForStatement*) { return true; }

bool LLVMVisitor::visitWhileStatement(WhileStatement*) { return true; }
bool LLVMVisitor::visitWhileStatement(const WhileStatement*) { return true; }

bool LLVMVisitor::leaveWhileStatement(WhileStatement*) { return true; }
bool LLVMVisitor::leaveWhileStatement(const WhileStatement*) { return true; }

bool LLVMVisitor::visitDoWhileStatement(DoWhileStatement*) { return true; }
bool LLVMVisitor::visitDoWhileStatement(const DoWhileStatement*) { return true; }

bool LLVMVisitor::leaveDoWhileStatement(DoWhileStatement*) { return true; }
bool LLVMVisitor::leaveDoWhileStatement(const DoWhileStatement*) { return true; }

bool LLVMVisitor::visitIfFollowStatement(IfFollowStatement*) { return true; }
bool LLVMVisitor::visitIfFollowStatement(const IfFollowStatement*) { return true; }

bool LLVMVisitor::leaveIfFollowStatement(IfFollowStatement*) { return true; }
bool LLVMVisitor::leaveIfFollowStatement(const IfFollowStatement*) { return true; }

bool LLVMVisitor::visitIfStatement(IfStatement*) { return true; }
bool LLVMVisitor::visitIfStatement(const IfStatement*) { return true; }

bool LLVMVisitor::leaveIfStatement(IfStatement*) { return true; }
bool LLVMVisitor::leaveIfStatement(const IfStatement*) { return true; }

bool LLVMVisitor::visitPrimativeExpression(const PrimativeExpression*) { return true; }

bool LLVMVisitor::leavePrimativeExpression(PrimativeExpression*) { return true; }
bool LLVMVisitor::leavePrimativeExpression(const PrimativeExpression*) { return true; }

bool LLVMVisitor::visitBreakStatement(BreakStatement*) { return true; }
bool LLVMVisitor::visitBreakStatement(const BreakStatement*) { return true; }

bool LLVMVisitor::leaveBreakStatement(BreakStatement*) { return true; }
bool LLVMVisitor::leaveBreakStatement(const BreakStatement*) { return true; }

bool LLVMVisitor::visitContinueStatement(ContinueStatement*) { return true; }
bool LLVMVisitor::visitContinueStatement(const ContinueStatement*) { return true; }

bool LLVMVisitor::leaveContinueStatement(ContinueStatement*) { return true; }
bool LLVMVisitor::leaveContinueStatement(const ContinueStatement*) { return true; }

bool LLVMVisitor::visitIdList(IdList*) { return true; }
bool LLVMVisitor::visitIdList(const IdList*) { return true; }

bool LLVMVisitor::leaveIdList(IdList*) { return true; }
bool LLVMVisitor::leaveIdList(const IdList*) { return true; }

bool LLVMVisitor::visitTypeFollows(TypeFollows*) { return true; }
bool LLVMVisitor::visitTypeFollows(const TypeFollows*) { return true; }

bool LLVMVisitor::leaveTypeFollows(TypeFollows*) { return true; }
bool LLVMVisitor::leaveTypeFollows(const TypeFollows*) { return true; }

bool LLVMVisitor::visitModifier(Modifier*) { return true; }
bool LLVMVisitor::visitModifier(const Modifier*) { return true; }

bool LLVMVisitor::leaveModifier(Modifier*) { return true; }
bool LLVMVisitor::leaveModifier(const Modifier*) { return true; }

bool LLVMVisitor::visitInitLists(InitLists*) { return true; }
bool LLVMVisitor::visitInitLists(const InitLists*) { return true; }

bool LLVMVisitor::leaveInitLists(InitLists*) { return true; }
bool LLVMVisitor::leaveInitLists(const InitLists*) { return true; }

bool LLVMVisitor::visitDelOrFun(DelOrFun*) { return true; }
bool LLVMVisitor::visitDelOrFun(const DelOrFun*) { return true; }

bool LLVMVisitor::leaveDelOrFun(DelOrFun*) { return true; }
bool LLVMVisitor::leaveDelOrFun(const DelOrFun*) { return true; }

bool LLVMVisitor::visitUnnamedArgList(UnnamedArgList*) { return true; }
bool LLVMVisitor::visitUnnamedArgList(const UnnamedArgList*) { return true; }

bool LLVMVisitor::leaveUnnamedArgList(UnnamedArgList*) { return true; }
bool LLVMVisitor::leaveUnnamedArgList(const UnnamedArgList*) { return true; }

bool LLVMVisitor::visitUnnamedArg(UnnamedArg*) { return true; }
bool LLVMVisitor::visitUnnamedArg(const UnnamedArg*) { return true; }

bool LLVMVisitor::leaveUnnamedArg(UnnamedArg*) { return true; }
bool LLVMVisitor::leaveUnnamedArg(const UnnamedArg*) { return true; }

bool LLVMVisitor::visitTypeDelFun(TypeDelFun*) { return true; }
bool LLVMVisitor::visitTypeDelFun(const TypeDelFun*) { return true; }

bool LLVMVisitor::leaveTypeDelFun(TypeDelFun*) { return true; }
bool LLVMVisitor::leaveTypeDelFun(const TypeDelFun*) { return true; }

bool LLVMVisitor::visitDecl(Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::visitDecl(Decl*) not implemented");
	return true;
}

bool LLVMVisitor::visitDecl(const Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::visitDecl(const Decl*) not implemented");
	return true;
}

bool LLVMVisitor::leaveDecl(Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::leaveDecl(Decl*) not implemented");
	return true;
}

bool LLVMVisitor::leaveDecl(const Decl*) {
	ASSERT_T_MSG(false, "LLVMVisitor::leaveDecl(const Decl*) not implemented");
	return true;
}
