#pragma once
#include "test_class.h"
#include "basic_test.h"

template<size_t size>
class MultiTest : public TestClass {
public:
	MultiTest(bool use_file) : TestClass("MultiTest", use_file) {};
	~MultiTest() = default;

	void Test() override {
		BasicTest<100> test(m_use_file);
	};
};