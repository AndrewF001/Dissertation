#pragma once
#include "file_handler.h"
#include "test_class.h"
#include "tsplib_data.h"

class TSPLib : public TestClass {
public:
	TSPLib(bool use_file) : TestClass("TSPLib", false) {};
	~TSPLib() = default;

	template<size_t Size>
	inline static std::array<Type2d, Size> gatherCities(std::string path) {
		std::array<Type2d, Size> output;
		//std::string file = readFromFile(path);

		return output;
	}

	void Test() override {
		std::string path = "E:\\Dissertation\\CPP_Libraries\\TSPLib";
		//std::cout << "Path to .tsp directory: ";
		//std::cin >> path;

		auto files = listFiles(path, ".tsp");
		auto input = selectTest(files);

		if (input == 1)
			selectAll(files);
		else
			selectOne(files[input - 2], tsplib::SIZES_seq{});
	};

private:

	int selectTest(std::vector<std::filesystem::directory_entry>& files) {
		std::cout << "Select test:\n";
		std::cout << "1. All\n";
		
		int i = 2;
		for (const auto& f : files) {
			std::cout << i++ << ". " << f.path().filename().string() << "\n";
		}

		int input;
		std::cin >> input;

		if (input < 1 || input > files.size() + 1)
			return selectTest(files);

		return input;
	}

	

	template<size_t Size>
	static Square maxPoints(std::array<Type2d, Size> const& data) {
		Square output;
		
		for (const auto& d : data) {
			if (d.m_x > output.m_p2.m_x)
				output.m_p2.m_x = d.m_x;
			if (d.m_x < output.m_p1.m_x)
				output.m_p1.m_x = d.m_x;
			if (d.m_y > output.m_p2.m_y)
				output.m_p2.m_y = d.m_y;
			if (d.m_y < output.m_p1.m_y)
				output.m_p1.m_y = d.m_y;
		}

		return output;
	};

	size_t getSize(std::filesystem::directory_entry f) {
		std::string s = readFromFile(f.path().string()).value();
		auto f1 = s.find("DIMENSION");
		f1 += 11;
		auto l1 = s.find("\n", f1);
		std::string size = s.substr(f1, l1 - f1);
		return std::stoull(size);
	}

	template<size_t Size>
	void _test(std::filesystem::directory_entry file) {
		std::cout << file.path().filename().string() << " : " << Size << "\n";
	}

	template <typename T, T... ints>
	void selectOne(std::filesystem::directory_entry file, std::integer_sequence<T, ints...> int_seq)
	{
		size_t size = getSize(file);
		((ints == size ? (void)(_test<ints>(file)) : (void)0), ...);
	}

	void selectAll(std::vector<std::filesystem::directory_entry> files)
	{
		for (const auto& f : files) {
			selectOne(f, tsplib::SIZES_seq{});
		}
	}

};
