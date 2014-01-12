#include <parser.hpp>
#include <error.hpp>
#include <lexer.hpp>
#include <symboltablevisitor.hpp>
#include <llvmvisitor.hpp>
#include <outvisitor.hpp>
#include <lambdavisitor.hpp>
#include <unittesthelper.hpp>

#include <logger.hpp>
#include <unit.hpp>

UNITTEST(primative1) {
	//LOG();
	LexParse lp("true && false || true");
	auto ast = lp.parser.parseOrOrExpression();
	StdOutVisitor ot(std::cout);
	//ast->acceptVisitor(ot);
	SymbolTableVisitor stv;
	//ast->acceptVisitor(stv);

	LLVMVisitor llvmV;
	ast->acceptVisitor(llvmV);
}

UNITTEST(add1) {
	//LOG();
	LexParse lp("10 + 2");
	auto ast = lp.parser.parseOrOrExpression();
	StdOutVisitor ot(std::cout);
	//ast->acceptVisitor(ot);
	SymbolTableVisitor stv;
	//ast->acceptVisitor(stv);

	//LLVMVisitor llvmV;
	//ast->acceptVisitor(llvmV);
}

UNITTEST(add2) {
	//LOG();
	LexParse lp("10.0f + 2.2f");
	auto ast = lp.parser.parseOrOrExpression();
	StdOutVisitor ot(std::cout);
	//ast->acceptVisitor(ot);
	SymbolTableVisitor stv;
	//ast->acceptVisitor(stv);

	LLVMVisitor llvmV;
	ast->acceptVisitor(llvmV);
}

UNITTEST(add3) {
	//LOG();
	LexParse lp("10.0f + 2.2f");
	auto ast = lp.parser.parseOrOrExpression();
	StdOutVisitor ot(std::cout);
	//ast->acceptVisitor(ot);
	SymbolTableVisitor stv;
	//ast->acceptVisitor(stv);

	LLVMVisitor llvmV;
	ast->acceptVisitor(llvmV);
}
