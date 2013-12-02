#include <parser.hpp>
#include <logger.hpp>
#include <unit.hpp>
#include <outvisitor.hpp>
#include <dotvisitor.hpp>

int main() {
	SweetLogger::enableLogger(1);
	auto testsPassed = Unit::runTests();
	auto numTests = Unit::getTests().size();
	LOG(1, "Number of tests ran '%u' all passed '%s' number of asserts '%u'", 
		numTests, !testsPassed ? "true" : "false", Unit::getNumOfAsserts());
	return 0;
}
