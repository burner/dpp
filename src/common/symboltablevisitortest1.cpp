#include <parser.hpp>
#include <error.hpp>
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

UNITTEST(typeTest1) {
	std::vector<std::string> varDecls = {
		"var constDelArr : int[] delegate(var : foo[]*) const []",
		"var constDelArr : int[] function(var : foo[]*) const []",
		"var constDelArr : int[] delegate(var : foo[] const*) const []",
		"var constDelArr : int[] function(var : foo[] const*) const []",
		"var name(1337)",
		"const name(1337 != 1337)",
		"const name : int[](1337, 55)",
		"var name : const int const * const []",
		"var name : const int const * const [](127,666)"
		"var name : int const * const []",
		"var name : int const * const [](127,666)"
		"var name : int const * []",
		"var name : int const * [](127,666)"
		"const name : const int const * const []",
		"const name : const int const * const [](127,666)"
	};
	for(auto& it : varDecls) {
		auto ss = std::make_shared<std::stringstream>(it);
		Lexer l(ss);
		Parser p(l);
		VarDeclPtr ast;
	   	try {
			ast = p.parseVarDecl();
		} catch(ParseException& e) {
			AS_T_C(false, [&]() {
				LOG(it);		
				LOG(e.what());		
			});
		}
		SymbolTableVisitor stv;
		ast->acceptVisitor(stv);

		bool worked(true);
		LambdaVisitor lv([&worked](const AstNode* n) {
			worked = worked && n->getSymbolTable() != nullptr;
			return n->getSymbolTable() != nullptr;
		});
		ast->acceptVisitor(lv);
		AS_T_MSG(worked, it);
	}
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

UNITTEST(functionDecl3) {
	auto ss = std::make_shared<std::stringstream>
		("def int bar(var foo : int) { return foo+2; }");
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

UNITTEST(functionDecl4) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " if(a ? b : c) {"
		 " }"
		 "}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}

UNITTEST(functionDecl5) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {\n"
		 " var a(true); \n"
		 " var b : bool(true); \n"
		 " var c : bool(false); \n"
		 " if(a ? b : c) {\n"
		 "  for(; a < b; ) somelabel {\n"
		 "   if(b == 0) {\n"
		 "    break somelabel;\n"
		 "   }\n"
		 "  }\n"
		 " }\n"
		 "}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}

UNITTEST(functionDecl6) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {\n"
		 " def bool fun() {\n"
		 "  return false;\n"
		 " }\n"
		 " var a(true); \n"
		 " var b : bool(true); \n"
		 " var c : bool(false); \n"
		 " if(a ? b : c) {\n"
		 "  for(; a < b; ) somelabel {\n"
		 "   if(b == 0 && fun()) {\n"
		 "    break somelabel;\n"
		 "   }\n"
		 "  }\n"
		 " }\n"
		 " return true;"
		 "}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}

UNITTEST(externDecl1) {
	auto ss = std::make_shared<std::stringstream>(
		"extern def int read(var a : int, var b : float);"
		"extern def int write(var a : int, var b : float);"
		"extern def int print(var a : const char*);");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
	SymbolTableVisitor stv;
	ast->acceptVisitor(stv);

	bool worked(true);
	LambdaVisitor lv([&worked](const AstNode* n) {
		worked = worked && n->getSymbolTable() != nullptr;
		return n->getSymbolTable() != nullptr;
	});
	ast->acceptVisitor(lv);
	AS_T(worked);
}
