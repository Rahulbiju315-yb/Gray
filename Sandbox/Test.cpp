#include "Test.h"
#include "TestDer.h"

Test* Test::createTest()
{
	return (new TestDer());
}
