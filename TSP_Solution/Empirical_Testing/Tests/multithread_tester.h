#pragma once
#include <windows.h>

#include "tsp_template.h"

// Honestly no clue how this works
int getPhysicalCoreCount() {
	DWORD length = 0;
	GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &length);

	std::vector<uint8_t> buffer(length);
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info =
		reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.data());

	if (!GetLogicalProcessorInformationEx(RelationProcessorCore, info, &length))
		return -1;

	int coreCount = 0;
	for (DWORD offset = 0; offset < length; offset += info->Size) {
		info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(
			buffer.data() + offset);
		if (info->Relationship == RelationProcessorCore)
			++coreCount;
	}
	return coreCount;
}



const Square AREA = { {0, 0}, 1000, 1000 };
constexpr std::array<size_t, 10> SIZES{ 10, 100, 200, 300, 500, 1000, 2000, 3000, 4000, 5000 };

class Tester {
public:
	Tester() : m_max_threads(getPhysicalCoreCount() - 1) {
		for (size_t i = 0; i < m_max_threads; i++) {
			m_threads.emplace_back();
		}
	};

	inline static unsigned int seed_gen() {

		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		return (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(now).count();	// TODO: potential loss of data
	}

	template<size_t Size>
	inline static std::array<Type2d, Size> generateCities(unsigned int seed) {
		std::mt19937 engine(seed);
		return TspDataTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree>::generateCities(AREA, GenerationType::rectangle, engine);
	}

	template<size_t Size, ConstructionType Con, OptimisationType Opt>
	void TestAlgorithm(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto thread = freeThread();

		std::promise<TSPVerboseResultDynamic> promise;
		m_results.emplace_back(promise.get_future());

		*thread = std::thread([this, promise = std::move(promise), seed, cities, args]() mutable {
			auto algorithm = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, Con, Opt>>(AREA, cities, GenerationType::rectangle, seed);
			promise.set_value(algorithm->run(args));
			});
	};

	std::vector<TSPVerboseResultDynamic> collectResults() {
		for (auto& thread : m_threads) {
			thread.join();
		}

		std::vector<TSPVerboseResultDynamic> output;

		for (auto& promise : m_results) {
			output.push_back(promise.get());
		}

		m_results.clear();
		return output;
	}

private:
	const unsigned int m_max_threads;

	std::vector<std::future<TSPVerboseResultDynamic>> m_results;
	std::vector<std::thread> m_threads;

	std::thread* freeThread() {
		
		// Find a new thread
		for (auto& thread : m_threads) {
			if (thread.get_id() == std::thread::id())
			{
				return &thread;
			}
		}

		// Find a finished thread
		while (true) {
			for (auto& thread : m_threads) {
				if (thread.joinable()) {
					thread.join();
					return &thread;
				}
			}
		}
	}



};
