#pragma once
#include <iostream>
#include <string>

static size_t LOGLEVEL = 0;

namespace Logger
{
	static void log(const std::string& message, const int level = 1) {
		if (LOGLEVEL > level)
			std::cout << message << std::flush;
	}

	static void log(const std::stringstream& message, const int level = 1) {
		if (LOGLEVEL > level)
			std::cout << message.str() << std::flush;
	}


	static void error(const std::string& message) {
		//if (LOGLEVEL > 0)
			std::cerr << message << std::fflush;
	}

	static void error(const std::stringstream& message) {
		//if (LOGLEVEL > 0)
			std::cerr << message.str() << std::fflush;
	}
}

