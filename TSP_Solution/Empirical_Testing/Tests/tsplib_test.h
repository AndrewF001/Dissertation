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
		siveFiles(files);

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
			auto& p = d.getPoint();
			if (p.m_x > output.m_p2.m_x)
				output.m_p2.m_x = p.m_x;
			if (p.m_x < output.m_p1.m_x)
				output.m_p1.m_x = p.m_x;
			if (p.m_y > output.m_p2.m_y)
				output.m_p2.m_y = p.m_y;
			if (p.m_y < output.m_p1.m_y)
				output.m_p1.m_y = p.m_y;
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
	std::unique_ptr<std::array<Type2d, Size>> readCities(std::filesystem::directory_entry& file) {
		// Read file
		std::optional<std::vector<std::string>> s = readLinesFromFile(file.path().string());
		if (!s.has_value())
			return nullptr;

		auto output = std::make_unique<std::array<Type2d, Size>>();
		
		// Find the NODE_COORD_SECTION
		size_t idx = 0;
		auto data = s.value();
		for (; idx < data.size(); idx++) {
			if (data[idx].find("NODE_COORD_SECTION") != std::string::npos)
				break;
		}
		idx++;

		// Read the cities data
		for (size_t i = 0; i < Size; i++) {
			std::vector<std::string> result;
			std::istringstream iss(data[idx + i]);
			for (std::string s; iss >> s; )	// Split the whitespace separated string
				result.push_back(s);

			Point2D p(std::stod(result[1]), std::stod(result[2]));
			(*output)[i] = Type2d(p);
		}
		return output;
	}

	template<size_t Size>
	void _test(std::filesystem::directory_entry file) {
		std::cout << file.path().filename().string() << " : " << Size << "\n";
		auto cities = readCities<Size>(file);
		auto area = maxPoints<Size>(*cities);

		TSPArgs args{ .max_depth = 8, .timeout_ms = std::chrono::milliseconds(1800000) };

		auto algorithm = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::DynamicLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, *cities);
		auto result = algorithm->run(args);
	}

	template <typename T, T... ints>
	void selectOne(std::filesystem::directory_entry file, std::integer_sequence<T, ints...> int_seq) {
		size_t size = getSize(file);
		((ints == size ? (void)(_test<ints>(file)) : (void)0), ...);
	}

	void selectAll(std::vector<std::filesystem::directory_entry> files) {
		for (const auto& f : files)
			selectOne(f, tsplib::SIZES_seq{});
	}

	void siveFiles(std::vector<std::filesystem::directory_entry>& files) {
		std::vector<std::pair<std::size_t, std::filesystem::directory_entry>> sizes;

		for (size_t i = 0; i < files.size(); i++) {
			std::string s = readFromFile(files[i].path().string()).value();

			if (s.find("NODE_COORD_SECTION") == std::string::npos) {
				files.erase(files.begin() + i);
				i--;
				continue;
			}

			auto f1 = s.find("EDGE_WEIGHT_TYPE");
			f1 += 19;
			auto l1 = s.find("\n", f1);
			std::string type = s.substr(f1, l1 - f1);
			if (type != "EUC_2D") {
				files.erase(files.begin() + i);
				i--;
				continue;
			}

			auto f2 = s.find("TYPE");
			f2 += 7;
			auto l2 = s.find("\n", f2);
			std::string type2 = s.substr(f2, l2 - f2);
			if (type2 != "TSP") {
				files.erase(files.begin() + i);
				i--;
				continue;
			}

			auto f3 = s.find("DIMENSION");
			f3 += 11;
			auto l3 = s.find("\n", f3);
			std::string size = s.substr(f3, l3 - f3);
			sizes.push_back(std::make_pair(std::stoull(size), files[i]));
		}

		files.clear();
		std::sort(sizes.begin(), sizes.end(), [](auto& a, auto& b) { return a.first < b.first; });
		for (const auto& p : sizes)
			files.push_back(p.second);

		for (const auto& f : sizes)
		{
			std::cout << f.first << ",";
		}

		std::cout << "\n\n";
	}

};
