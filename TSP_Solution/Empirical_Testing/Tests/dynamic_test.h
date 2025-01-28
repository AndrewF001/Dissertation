#pragma once
#include "test_class.h"

class DynamicTest : public TestClass {
public:
	DynamicTest(bool use_file) : TestClass("DynamicTest", use_file) {};
	~DynamicTest() = default;

	void Test() override {

	};
};