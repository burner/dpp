#pragma once

#include <error.hpp>
#include <lexer.hpp>
#include <parser.hpp>

struct LexParse {
	LexParse() = delete;
	LexParse(const std::string&);

	std::shared_ptr<std::stringstream> ssp;
	Lexer lexer;
	Parser parser;
};
