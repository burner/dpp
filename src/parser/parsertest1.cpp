#include <parser.hpp>
#include <logger.hpp>
#include <unit.hpp>
#include <outvisitor.hpp>
#include <dotvisitor.hpp>
#include <llvmvisitor.hpp>
#include <unittesthelper.hpp>

UNITTEST(rel1) {
	LexParse lp("hello <= (foobar)");
	auto ast = lp.parser.parseOrOrExpression();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(assign1) {
	LexParse lp
		("hello = (foobar)");
	auto ast = lp.parser.parseAssignmentExpression();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(post1) {
	LexParse lp
		("hello.world()");
	auto ast = lp.parser.parseAssignmentExpression();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(varDecl1) {
	LexParse lp
		("var foo(10) ");
	auto ast = lp.parser.parseVarDecl();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(varDecl2) {
	LexParse lp
		("var bar : int");
	auto ast = lp.parser.parseVarDecl();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(argList1) {
	LexParse lp
		("var bar : int, var foo : float");
	auto ast = lp.parser.parseArgumentList();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(blockStmt1) {
	LexParse lp
		("{}");
	auto ast = lp.parser.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(blockStmt2) {
	LexParse lp
		("{{}}");
	auto ast = lp.parser.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(blockStmt3) {
	LexParse lp
		("{{}{}}");
	auto ast = lp.parser.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(blockStmt4) {
	LexParse lp
		("{foobar();}");
	auto ast = lp.parser.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(iterStmt1) {
	LexParse lp
		("{ while(bar()) { }}");
	auto ast = lp.parser.parseStatement();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(function1) {
	LexParse lp
		("def int foo() {}");
	auto ast = lp.parser.parseFunctionDecl();
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}
UNITTEST(function2) {
	LexParse lp
		("def int foo(var argc : int, const argv : int[]) {}");
	auto ast = lp.parser.parseFunctionDecl();
	std::ofstream z("test2.dot");
	DotVisitor d(z);
	//ast->acceptVisitor(d);
	StdOutVisitor v(std::cout);
	//ast->acceptVisitor(v);
}

UNITTEST(unary1) {
	LexParse lp
		("hello");
	auto ast = lp.parser.parseMulExpression();
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
	LexParse lp
		("extern def int read(var a : int, var b : float);"
		"extern def int write(var a : int, var b : float);");
	auto ast = lp.parser.parseDecl();
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
	LexParse lp
		("def int main() {"
		 " if(a ? b : c) {"
		 " }"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}

UNITTEST(ifelse2) {
	LexParse lp
		("def int main() {"
		 " if(a ? b : c) {"
		 " } else {}"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}

UNITTEST(ifelse3) {
	LexParse lp
		("def int main() {"
		 " if(a ? b : c) {"
		 " } else if(true) {"
		 " } else {}"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}

UNITTEST(do1) {
	LexParse lp
		("def int main() {"
		 " do {"
		 " } while(false);"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}

UNITTEST(for1) {
	LexParse lp
		("def int main() {"
		 " for(;;) {"
		 " }"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}

UNITTEST(for2) {
	LexParse lp
		("def int main() {"
		 " for(;;) {"
		 "  for(var f(128); f > 0; --f) {"
		 "  }"
		 " }"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}

UNITTEST(for3) {
	LexParse lp
		("def int main() {"
		 " for(;;) outer {"
		 "  for(var f(128); f > 0; --f) {"
		 "  }"
		 " }"
		 "}");
		 
	auto ast = lp.parser.parseDecl();
}
