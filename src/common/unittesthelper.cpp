#include <unittesthelper.hpp>

LexParse::LexParse(const std::string& s) :
	ssp(std::make_shared<std::stringstream>(s)),
	lexer(ssp), parser(lexer) 
{
}
