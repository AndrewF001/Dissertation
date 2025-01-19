#pragma once
#include "../test_class.h"

class example : public TestClass {
public:
	example(std::string n, size_t p = 1, std::chrono::seconds t = std::chrono::seconds::max()) : TestClass(n, p, t) {};
	~example() = default;

	void Test() override {

	};
};