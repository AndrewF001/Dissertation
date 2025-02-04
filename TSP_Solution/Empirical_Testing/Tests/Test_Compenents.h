#pragma once
#include <tsp_template.h>


const Square AREA = { {0, 0}, 1000, 1000 };
constexpr std::array<size_t, 10> SIZES{ 10, 100, 200, 300, 500, 1000, 2000, 3000, 4000, 5000 };

namespace Tests {

	inline static unsigned int seed_gen() {
		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		return (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(now).count();	// TODO: potential loss of data
	}

	template<size_t Size>
	inline static std::array<Type2d, Size> generateCities(unsigned int seed) {
		std::mt19937 engine(seed);
		return TspDataTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree>::generateCities(AREA, GenerationType::rectangle, engine);
	}

	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestConvexHullInsertion(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::ConvexHullInsertion, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};

	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestNearestNeighbour(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::NearestNeighbour, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};

	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestShortestInsertion(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::ShortestInsertion, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};


	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestStaticLookahead(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookahead, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};

	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestStaticLookaheadConvexHullInserstion(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};

	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestDynamicLookahead(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::DynamicLookahead, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};

	template<size_t Size, OptimisationType Opt>
	inline static TSPVerboseResultDynamic TestDynamicLookaheadConvexHullInserstion(unsigned int seed, std::array<Type2d, Size>& cities, TSPArgs& args) {
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::DynamicLookaheadConvexHullInserstion, Opt>>(AREA, cities, GenerationType::rectangle, seed);
		return ConvexHullInsertion->run(args);
	};

}