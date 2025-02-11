#pragma once
#include <string>
#include <fstream>
#include <filesystem>

namespace FileHandler {

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

	static std::optional<std::string> readFromFile(const std::string& path) {
		std::ifstream file(path);

		if (!file.is_open())
			return std::nullopt;

		std::string data;
		std::string line;
		while (std::getline(file, line)) {
			data += line + "\n";
		}

		file.close();
		return data;
	}

	static std::optional<std::vector<std::string>> readLinesFromFile(const std::string& path) {
		std::ifstream file(path);
		if (!file.is_open())
			return std::nullopt;

		std::vector<std::string> lines;
		std::string line;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		return lines;
	}

	static bool fileExists(const std::string& path) {
		std::ifstream file(path);
		return file.good();
	}

	static std::string nextFileName(const std::string& path) {
		int i = 1;
		std::string extension = "";
		while (fileExists(path + extension)) {
			extension = "(" + std::to_string(i++) + ")";
		}
		return path + extension;
	}

	static std::vector<std::filesystem::directory_entry> listFiles(const std::string& path, const std::string& extension) {
		std::vector<std::filesystem::directory_entry> files;
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.path().extension() == extension)
				files.push_back(entry);
		}
		return files;
	}
}

//std::optional<std::vector<uint8_t>> readFromFile(const std::string& path)
//{
//	std::ifstream file(path, std::ios::binary);
//	
//	if (!file.is_open())
//		return std::nullopt;
//	
//	file.unsetf(std::ios::skipws);
//
//	std::streampos fileSize;
//	file.seekg(0, std::ios::end);
//	fileSize = file.tellg();
//	file.seekg(0, std::ios::beg);
//
//	std::vector<uint8_t> vec;
//	vec.reserve(fileSize);
//
//	vec.insert(vec.begin(),
//		std::istream_iterator<uint8_t>(file),
//		std::istream_iterator<uint8_t>());
//
//	return vec;
//}
//
//
//template<typename T>
//std::vector<uint8_t> objectToBytes(const T* data, size_t number = 1) {
//	return std::vector<uint8_t>(reinterpret_cast<const uint8_t*>(data), reinterpret_cast<const uint8_t*>(data) + sizeof(T) * number);
//}
//
//template<typename T>
//T bytesToObject(const uint8_t* data) {
//	T output;
//	std::memcpy(&output, data, sizeof(T));
//	return output;
//}

//template<typename T>
//std::vector<T> bytesToObject(const uint8_t* data, size_t number = 1) {
//	std::vector<T> output(number);
//	std::memcpy(output.data(), data, sizeof(T) * number);
//	return output;
//}


template<typename T>
std::string objectToString(const T* data) {
	return std::string(reinterpret_cast<const char*>(data), sizeof(T));
}

template<typename T>
T stringToObject(const char* data) {
	T output;

	std::memcpy(&output, data, sizeof(T));

	//for (size_t i = 0; i < sizeof(T); i++)
	//	((char*)&output)[i] = data[i];

	return output;
}
//
//static void writeObjectToFile(const std::string& path, const void* data, size_t size) {
//	std::ofstream file;
//	file.open(path, std::ios::binary);
//	file.write((char*)data, size);
//	file.close();
//}
//
//static const void* readObjectFromFile(const std::string& path, size_t size) {
//	std::ifstream file;
//	file.open(path, std::ios::binary);
//	void* data = malloc(size);
//	file.read((char*)data, size);
//	file.close();
//	return data;
//}
