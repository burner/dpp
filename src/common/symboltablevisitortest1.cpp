#include <parser.hpp>
#include <symboltablevisitor.hpp>
#include <lambdavisitor.hpp>

#include <logger.hpp>
#include <unit.hpp>

UNITTEST(blockStmt1Test) {
	auto ss = std::make_shared<std::stringstream>
		("{}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseStatement();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	AS_EQ(stv.getRoot()->getFollow().size(), 1u);

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}

UNITTEST(functionDecl1) {
	auto ss = std::make_shared<std::stringstream>
		("def int bar() {}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	auto map = stv.getRoot()->getMap();
	AS_EQ(map.size(), 1u);

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}

UNITTEST(functionDecl2) {
	auto ss = std::make_shared<std::stringstream>
		("def int bar(var foo : int) {}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	auto map = stv.getRoot()->getMap();
	AS_T(map.count(SymbolTableEntry("bar")));
	AS_T(stv.getRoot()->contains("bar"));
	AS_EQ(stv.getRoot()->getFollow().size(), 1u);
	AS_T(stv.getRoot()->getFollow()[0]->contains("bar"));
	AS_F(stv.getRoot()->getFollow()[0]->contains("foo"));

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}
