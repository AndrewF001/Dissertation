#pragma once
#include <string>
#include <fstream>


static void writeToFile(const std::string& path, const std::string& data) {
	std::ofstream file;
	file.open(path);
	file << data;
	file.close();
}

static void appendToFile(const std::string& path, const std::string& data) {
	std::ofstream file;
	file.open(path, std::ios::app);
	file << data;
	file.close();
}

static std::string readFromFile(const std::string& path) {
	std::ifstream file;
	file.open(path);
	std::string data;
	std::string line;
	while (std::getline(file, line)) {
		data += line + "\n";
	}
	file.close();
	return data;
}