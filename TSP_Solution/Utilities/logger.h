#pragma once
#include <iostream>
#include <string>

#define LOGLEVEL 2

namespace Logger
{
	static void log(const std::string& message, const int level = 1) {
		if (LOGLEVEL > level)
			std::cout << message << std::endl;
	}

	static void log(const std::stringstream& message, const int level = 1) {
		if (LOGLEVEL > level)
			std::cout << message.str() << std::endl;
	}


	static void error(const std::string& message) {
		if constexpr (LOGLEVEL > 0)
			std::cerr << message << std::endl;
	}

	static void error(const std::stringstream& message) {
		if constexpr (LOGLEVEL > 0)
			std::cerr << message.str() << std::endl;
	}
}

