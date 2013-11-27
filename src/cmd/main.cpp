#include <parser.hpp>
#include <logger.hpp>
#include <unit.hpp>
#include <outvisitor.hpp>
#include <dotvisitor.hpp>

int main() {
	SweetLogger::enableLogger(1);
	auto testsPassed = Unit::runTests();
	auto numTests = Unit::getTests().size();
	LOG(1, "Number of tests run '%u' all passed '%s'", numTests, 
		!testsPassed ? "true" : "false");
	return 0;
}
