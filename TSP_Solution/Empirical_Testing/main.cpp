#include "Tests/example.h"
#include "Tests/basic_100_test.h"

int main(int argc, char* argv[]) {
	Basic100Test test("Basic_100_Test", 100);
	test.RunTests();
}
