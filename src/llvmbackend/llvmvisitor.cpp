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

		ASSERT_EQ(valueStack.size(), 0u);
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
		
		ASSERT_EQ(valueStack.size(), 1u);

		LLVMDump(this->valueStack.top());
	}
	return true;
}
