#pragma once
#include "file_handler.h"
#include "test_class.h"

class TSPLib : public TestClass {
public:
	TSPLib(bool use_file) : TestClass("TSPLib", use_file) {};
	~TSPLib() = default;

	template<size_t Size>
	inline static std::array<Type2d, Size> gatherCities(std::string path) {
		std::array<Type2d, Size> output;
		std::string file = readFromFile(path);

		return output;
	}

	void Test() override {
		
	};


private:



};