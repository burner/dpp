#include <parser.hpp>
#include <logger.hpp>
#include <unit.hpp>
#include <outvisitor.hpp>
#include <dotvisitor.hpp>
#include <llvmvisitor.hpp>

UNITTEST(rel1) {
	auto ss = std::make_shared<std::stringstream>
		("hello <= (foobar)");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseOrOrExpression();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(assign1) {
	auto ss = std::make_shared<std::stringstream>
		("hello = (foobar)");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseAssignmentExpression();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(varDecl1) {
	auto ss = std::make_shared<std::stringstream>
		("var foo(10) ");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseVarDecl();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(varDecl2) {
	auto ss = std::make_shared<std::stringstream>
		("var bar : int");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseVarDecl();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(argList1) {
	auto ss = std::make_shared<std::stringstream>
		("var bar : int, var foo : float");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseArgumentList();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(blockStmt1) {
	auto ss = std::make_shared<std::stringstream>
		("{}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(blockStmt2) {
	auto ss = std::make_shared<std::stringstream>
		("{{}}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(blockStmt3) {
	auto ss = std::make_shared<std::stringstream>
		("{{}{}}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(blockStmt4) {
	auto ss = std::make_shared<std::stringstream>
		("{foobar();}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(iterStmt1) {
	auto ss = std::make_shared<std::stringstream>
		("{ while(bar()) { }}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(function1) {
	auto ss = std::make_shared<std::stringstream>
		("def int foo() {}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(function2) {
	auto ss = std::make_shared<std::stringstream>
		("def int foo(var argc : int, const argv : int[]) {}");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseFunctionDecl();
	std::ofstream z("test2.dot");
	DotVisitor d(z);
	//ast->acceptVisitor(d);
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(unary1) {
	auto ss = std::make_shared<std::stringstream>
		("hello");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseMulExpression();
	StdOutVisitor v(std::cout);
	std::ofstream z("test.dot");
	DotVisitor d(z);
	LLVMVisitor ll;
	//ast->acceptVisitor(d);
	//std::cout<<std::endl;
	//ast->acceptVisitor(v);
	//std::cout<<std::endl;
	//ast->acceptVisitor(ll);
}

UNITTEST(extern1) {
	auto ss = std::make_shared<std::stringstream>
		("extern def int read(var a : int, var b : float);"
		"extern def int write(var a : int, var b : float);");
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
	StdOutVisitor v(std::cout);
	std::ofstream z("test.dot");
	DotVisitor d(z);
	LLVMVisitor ll;
	//ast->acceptVisitor(d);
	//std::cout<<std::endl;
	//ast->acceptVisitor(v);
	//std::cout<<std::endl;
	//ast->acceptVisitor(ll);
}

UNITTEST(ifelse1) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " if(a ? b : c) {"
		 " }"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}

UNITTEST(ifelse2) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " if(a ? b : c) {"
		 " } else {}"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}

UNITTEST(ifelse3) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " if(a ? b : c) {"
		 " } else if(true) {"
		 " } else {}"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}

UNITTEST(do1) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " do {"
		 " } while(false);"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}

UNITTEST(for1) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " for(;;) {"
		 " }"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}

UNITTEST(for2) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " for(;;) {"
		 "  for(var f(128); f > 0; --f) {"
		 "  }"
		 " }"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}

UNITTEST(for3) {
	auto ss = std::make_shared<std::stringstream>
		("def int main() {"
		 " for(;;) outer {"
		 "  for(var f(128); f > 0; --f) {"
		 "  }"
		 " }"
		 "}");
		 
	Lexer l(ss);
	Parser p(l);
	auto ast = p.parseDecl();
}
