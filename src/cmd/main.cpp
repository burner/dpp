#include <parser.hpp>
#include <logger.hpp>
#include <unit.hpp>
#include <outvisitor.hpp>
#include <dotvisitor.hpp>

int main() {
	sweet::enableLogger(1);
	auto testsPassed = sweet::Unit::runTests();
	auto numTests = sweet::Unit::getTests().size();
	LOG(1, "Number of tests ran '%u' all passed '%s' number of asserts '%u'", 
		numTests, !testsPassed ? "true" : "false", sweet::Unit::getNumOfAsserts());
	return 0;
}
