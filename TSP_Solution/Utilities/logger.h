#pragma once
#include <iostream>
#include <string>

#define LOGLEVEL 2

namespace Logger
{
	static void log(const std::string& message) {
		if constexpr (LOGLEVEL > 1)
			std::cout << message << std::endl;
	}

	static void error(const std::string& message) {
		if constexpr (LOGLEVEL > 0)
			std::cerr << message << std::endl;
	}
}

