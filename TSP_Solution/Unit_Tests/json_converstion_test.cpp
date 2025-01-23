#include "pch.h"
#include "gtest/gtest.h"
#include "file_handling/json_convertion.h"

namespace {
	using namespace jsonconversion;

	TEST(JsonConversionTest, DocumentTest) {
		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;
		val.SetInt(1);
		doc.AddMember("test", val, doc.GetAllocator());
		auto s = documentToString(doc);
		EXPECT_EQ(s, "{\n    \"test\": 1\n}");

		auto d = stringToDocument(s);
		EXPECT_EQ(d["test"].GetInt(), 1);
	}

	TEST(JsonConversionTest, Point2DTest) {
		Point2D point = { 1, 2 };
		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;

		jsonconversion::point2DToJSON(point, val, doc.GetAllocator());
		doc.AddMember("point", val, doc.GetAllocator());
		auto p = jsonconversion::JSONToPoint2D(doc["point"]);

		EXPECT_EQ(point.m_x, p.m_x);
		EXPECT_EQ(point.m_y, p.m_y);
	}

	TEST(JsonConversionTest, SquareTest) {
		Square square = { {1, 2}, {3, 4} };
		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;

		jsonconversion::squareToJSON(square, val, doc.GetAllocator());
		doc.AddMember("square", val, doc.GetAllocator());
		auto s = jsonconversion::JSONToSquare(doc["square"]);

		EXPECT_EQ(square.m_p1.m_x, s.m_p1.m_x);
		EXPECT_EQ(square.m_p1.m_y, s.m_p1.m_y);
		EXPECT_EQ(square.m_p2.m_x, s.m_p2.m_x);
		EXPECT_EQ(square.m_p2.m_y, s.m_p2.m_y);
	}

	TEST(JsonConversionTest, ValidtyTest) {
		EXPECT_EQ(stringToValidity(validityToString(Validity::Valid)), Validity::Valid);
		EXPECT_EQ(stringToValidity(validityToString(Validity::Invalid)), Validity::Invalid);
		EXPECT_EQ(stringToValidity(validityToString(Validity::Timeout)), Validity::Timeout);
	}

	TEST(JsonConversionTest, GenerationTest) {
		EXPECT_EQ(stringToGenerationType(GenerationTypeToString(GenerationType::areaCode)), GenerationType::areaCode);
		EXPECT_EQ(stringToGenerationType(GenerationTypeToString(GenerationType::rectangle)), GenerationType::rectangle);
		EXPECT_EQ(stringToGenerationType(GenerationTypeToString(GenerationType::circle)), GenerationType::circle);
	}

	TEST(JsonConversionTest, CachingTest) {
		EXPECT_EQ(stringToCachingType(cachingTypeToString(CachingType::full)), CachingType::full);
		EXPECT_EQ(stringToCachingType(cachingTypeToString(CachingType::none)), CachingType::none);
		EXPECT_EQ(stringToCachingType(cachingTypeToString(CachingType::partial)), CachingType::partial);
	}

	TEST(JsonConversionTest, PartitioningTest) {
		EXPECT_EQ(stringToPartitioningType(partitioningTypeToString(PartitioningType::linearSearch)), PartitioningType::linearSearch);
		EXPECT_EQ(stringToPartitioningType(partitioningTypeToString(PartitioningType::quadTree)), PartitioningType::quadTree);
	}

	TEST(JsonConversionTest, OptimisationTest) {
		EXPECT_EQ(stringToOptimisationType(optimisationTypeToString(OptimisationType::None)), OptimisationType::None);
		EXPECT_EQ(stringToOptimisationType(optimisationTypeToString(OptimisationType::ThreeOpt)), OptimisationType::ThreeOpt);
		EXPECT_EQ(stringToOptimisationType(optimisationTypeToString(OptimisationType::TwoOpt)), OptimisationType::TwoOpt);
	}

	TEST(JsonConversionTest, ConstructionTest) {
		EXPECT_EQ(stringToConstructionType(constructionTypeToString(ConstructionType::ConvexHullInsertion)), ConstructionType::ConvexHullInsertion);
		EXPECT_EQ(stringToConstructionType(constructionTypeToString(ConstructionType::NearestNeighbour)), ConstructionType::NearestNeighbour);
		EXPECT_EQ(stringToConstructionType(constructionTypeToString(ConstructionType::ShortestInsertion)), ConstructionType::ShortestInsertion);
		EXPECT_EQ(stringToConstructionType(constructionTypeToString(ConstructionType::StaticLookaheadConvexHullInserstion)), ConstructionType::StaticLookaheadConvexHullInserstion);
	}

	TEST(JsonConversionTest, TimeScaleTest) {
		TimeScale t1(100);
		EXPECT_EQ(stringToTimeScale(timeScaletoString(t1)), t1);
	}

	TEST(JsonConversionTest, RunModeTest) {
		RunMode s;
		s.num_cities = 10;
		s.genType = GenerationType::rectangle;
		s.Caching = CachingType::full;
		s.Partitioning = PartitioningType::quadTree;
		s.Construction = ConstructionType::StaticLookaheadConvexHullInserstion;
		s.Optimisation = OptimisationType::TwoOpt;
		s.args = { 1, 2, std::chrono::milliseconds(100) };

		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;

		jsonconversion::runModeToJson(s, val, doc.GetAllocator());
		doc.AddMember("runMode", val, doc.GetAllocator());
		RunMode r;
		jsonconversion::JsonToRunMode(r, doc["runMode"]);

		EXPECT_EQ(s.num_cities, r.num_cities);
		EXPECT_EQ(s.genType, r.genType);
		EXPECT_EQ(s.Caching, r.Caching);
		EXPECT_EQ(s.Partitioning, r.Partitioning);
		EXPECT_EQ(s.Construction, r.Construction);
		EXPECT_EQ(s.Optimisation, r.Optimisation);
		EXPECT_EQ(s.args, r.args);
	}

	TEST(JsonConversionTest, TSPResultTest) {
		TSPResult s;
		s.num_cities = 10;
		s.genType = GenerationType::rectangle;
		s.Caching = CachingType::full;
		s.Partitioning = PartitioningType::quadTree;
		s.Construction = ConstructionType::StaticLookaheadConvexHullInserstion;
		s.Optimisation = OptimisationType::TwoOpt;
		s.args = { 1, 2, std::chrono::milliseconds(100) };
		s.area = { {1, 2}, {3, 4} };
		s.seed = 100;
		s.constructTour_distance = 100;
		s.final_distance = 200;
		s.validRoute = Validity::Valid;
		s.total_run_time = TimeScale(100);
		s.initalisePartition_time = TimeScale(200);

		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;

		jsonconversion::TSPResultToJson(s, val, doc.GetAllocator());
		doc.AddMember("TSPResult", val, doc.GetAllocator());
		TSPResult r;
		jsonconversion::JsonToTSPResult(r, doc["TSPResult"]);

		EXPECT_EQ(s.num_cities, r.num_cities);
		EXPECT_EQ(s.genType, r.genType);
		EXPECT_EQ(s.Caching, r.Caching);
		EXPECT_EQ(s.Partitioning, r.Partitioning);
		EXPECT_EQ(s.Construction, r.Construction);
		EXPECT_EQ(s.Optimisation, r.Optimisation);
		EXPECT_EQ(s.args, r.args);
		EXPECT_EQ(s.area.m_p1.m_x, r.area.m_p1.m_x);
		EXPECT_EQ(s.area.m_p1.m_y, r.area.m_p1.m_y);
		EXPECT_EQ(s.area.m_p2.m_x, r.area.m_p2.m_x);
		EXPECT_EQ(s.area.m_p2.m_y, r.area.m_p2.m_y);
		EXPECT_EQ(s.seed, r.seed);
		EXPECT_EQ(s.constructTour_distance, r.constructTour_distance);
		EXPECT_EQ(s.final_distance, r.final_distance);
		EXPECT_EQ(s.validRoute, r.validRoute);
		EXPECT_EQ(s.total_run_time, r.total_run_time);
		EXPECT_EQ(s.initalisePartition_time, r.initalisePartition_time);
	}

	TEST(JsonConversionTest, TSPVerboseResultDynamicTest) {
		TSPVerboseResultDynamic s;
		s.num_cities = 10;
		s.genType = GenerationType::rectangle;
		s.Caching = CachingType::full;
		s.Partitioning = PartitioningType::quadTree;
		s.Construction = ConstructionType::StaticLookaheadConvexHullInserstion;
		s.Optimisation = OptimisationType::TwoOpt;
		s.args = { 1, 2, std::chrono::milliseconds(100) };
		s.area = { {1, 2}, {3, 4} };
		s.seed = 100;
		s.constructTour_distance = 100;
		s.final_distance = 200;
		s.validRoute = Validity::Valid;
		s.total_run_time = TimeScale(100);
		s.initalisePartition_time = TimeScale(200);
		s.name = "Test";
		s.route = { 1, 2, 3, 4 };
		s.node_coord_section = { Type2d({1, 2}), Type2d({3, 4}) };

		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;

		jsonconversion::TSPVerboseResultDynamicToJson(s, val, doc.GetAllocator());
		doc.AddMember("TSPVerboseResultDynamic", val, doc.GetAllocator());
		TSPVerboseResultDynamic r;
		jsonconversion::JsonToTSPVerboseResultDynamic(r, doc["TSPVerboseResultDynamic"]);

		EXPECT_EQ(s.num_cities, r.num_cities);
		EXPECT_EQ(s.genType, r.genType);
		EXPECT_EQ(s.Caching, r.Caching);
		EXPECT_EQ(s.Partitioning, r.Partitioning);
		EXPECT_EQ(s.Construction, r.Construction);
		EXPECT_EQ(s.Optimisation, r.Optimisation);
		EXPECT_EQ(s.args, r.args);
		EXPECT_EQ(s.area.m_p1.m_x, r.area.m_p1.m_x);
		EXPECT_EQ(s.area.m_p1.m_y, r.area.m_p1.m_y);
		EXPECT_EQ(s.area.m_p2.m_x, r.area.m_p2.m_x);
		EXPECT_EQ(s.area.m_p2.m_y, r.area.m_p2.m_y);
		EXPECT_EQ(s.seed, r.seed);
		EXPECT_EQ(s.constructTour_distance, r.constructTour_distance);
		EXPECT_EQ(s.final_distance, r.final_distance);
		EXPECT_EQ(s.validRoute, r.validRoute);
		EXPECT_EQ(s.total_run_time, r.total_run_time);
		EXPECT_EQ(s.initalisePartition_time, r.initalisePartition_time);
		EXPECT_EQ(s.name, s.name);
		EXPECT_EQ(s.route[2], s.route[2]);
		EXPECT_EQ(s.node_coord_section[1].getPoint().m_y, s.node_coord_section[1].getPoint().m_y);
	}

	TEST(JsonConversionTest, StatisticEntryTest) {
		StatisticEntry s;
		s.num_cities = 10;
		s.genType = GenerationType::rectangle;
		s.Caching = CachingType::full;
		s.Partitioning = PartitioningType::quadTree;
		s.Construction = ConstructionType::StaticLookaheadConvexHullInserstion;
		s.Optimisation = OptimisationType::TwoOpt;
		s.args = { 1, 2, std::chrono::milliseconds(100) };
		s.number_of_runs = 100;
		s.total_constructTour_time = TimeScale(100);
		s.total_final_distance = 100;


		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value val;

		jsonconversion::StatisticEntryToJson(s, val, doc.GetAllocator());
		doc.AddMember("Statistic", val, doc.GetAllocator());
		StatisticEntry r;
		jsonconversion::JsonToStatisticEntry(r, doc["Statistic"]);

		EXPECT_EQ(s.num_cities, r.num_cities);
		EXPECT_EQ(s.genType, r.genType);
		EXPECT_EQ(s.Caching, r.Caching);
		EXPECT_EQ(s.Partitioning, r.Partitioning);
		EXPECT_EQ(s.Construction, r.Construction);
		EXPECT_EQ(s.Optimisation, r.Optimisation);
		EXPECT_EQ(s.args, r.args);
		EXPECT_EQ(s.number_of_runs, s.number_of_runs);
		EXPECT_EQ(s.total_constructTour_time, s.total_constructTour_time);
		EXPECT_EQ(s.total_final_distance, s.total_final_distance);
	}
}