#pragma once
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include "../tsp_data/tsp_constructs.h"
#include "../tour_optimisation/optimisation_headers.h"
#include "../tour_construction/consturction_headers.h"
#include "timer.h"
#include "tsp_structs.h"



namespace jsonconversion {

	static std::string documentToString(const rapidjson::Document& doc) {
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		return buffer.GetString();
	}

	static rapidjson::Document stringToDocument(const std::string& s) {
		rapidjson::Document doc;
		doc.Parse(s.c_str());
		return doc;
	}

	static void addStringMember(rapidjson::Value& v, const std::string& name, const std::string& value, rapidjson::Document::AllocatorType& a) {
		v.AddMember(rapidjson::Value(name.c_str(), a), rapidjson::Value(value.c_str(), a), a);
	}

	static std::string validityToString(Validity v) {
		switch (v) {
			case Validity::Valid:
				return "Valid";
			case Validity::Invalid:
				return "Invalid";
			case Validity::Timeout:
				return "Timeout";
		}
		return "N/A";
	}

	static Validity stringToValidity(const std::string& s) {
		if (s == "Valid")
			return Validity::Valid;
		if (s == "Invalid")
			return Validity::Invalid;
		if (s == "Timeout")
			return Validity::Timeout;
		return Invalid;
	}

	static std::string GenerationTypeToString(GenerationType g) {
		switch (g) {
			case GenerationType::rectangle:
				return "rectangle";
			case GenerationType::circle:
				return "circle";
			case GenerationType::areaCode:
				return "areaCode";
		}
		return "N/A";
	}

	static GenerationType stringToGenerationType(const std::string& s) {
		if (s == "rectangle")
			return GenerationType::rectangle;
		if (s == "circle")
			return GenerationType::circle;
		if (s == "areaCode")
			return GenerationType::areaCode;
		return GenerationType::rectangle;
	}

	static std::string cachingTypeToString(CachingType c) {
		switch (c) {
			case CachingType::full:
				return "full";
			case CachingType::partial:
				return "partial";
			case CachingType::none:
				return "none";
		}
		return "N/A";
	}

	static CachingType stringToCachingType(const std::string& s) {
		if (s == "full")
			return CachingType::full;
		if (s == "partial")
			return CachingType::partial;
		if (s == "none")
			return CachingType::none;
		return CachingType::none;
	}

	static std::string partitioningTypeToString(PartitioningType p) {
		switch (p) {
			case PartitioningType::linearSearch:
				return "linearSearch";
			case PartitioningType::quadTree:
				return "quadTree";
		}
		return "N/A";
	}

	static PartitioningType stringToPartitioningType(const std::string& s) {
		if (s == "linearSearch")
			return PartitioningType::linearSearch;
		if (s == "quadTree")
			return PartitioningType::quadTree;
		return PartitioningType::quadTree;
	}

	static std::string constructionTypeToString(ConstructionType c) {
		switch (c) {
			case ConstructionType::StaticLookaheadConvexHullInserstion:
				return "StaticLookaheadConvexHullInserstion";
			case ConstructionType::NearestNeighbour:
				return "NearestNeighbour";
			case ConstructionType::ShortestInsertion:
				return "ShortestInsertion";
			case ConstructionType::ConvexHullInsertion:
				return "ConvexHullInsertion";
			case ConstructionType::StaticLookahead:
				return "StaticLookahead";
			case ConstructionType::ConvexHull:
				return "ConvexHull";
			case ConstructionType::DynamicLookahead:
				return "DynamicLookahead";
			case ConstructionType::DynamicLookaheadConvexHullInserstion:
				return "DynamicLookaheadConvexHullInserstion";
		}
		return "N/A";
	}

	static ConstructionType stringToConstructionType(const std::string& s) {
		if (s == "StaticLookaheadConvexHullInserstion")
			return ConstructionType::StaticLookaheadConvexHullInserstion;
		if (s == "NearestNeighbour")
			return ConstructionType::NearestNeighbour;
		if (s == "ShortestInsertion")
			return ConstructionType::ShortestInsertion;
		if (s == "ConvexHullInsertion")
			return ConstructionType::ConvexHullInsertion;
		if (s == "StaticLookahead")
			return ConstructionType::StaticLookahead;
		if (s == "ConvexHull")
			return ConstructionType::ConvexHull;
		if (s == "DynamicLookahead")
			return ConstructionType::DynamicLookahead;
		if (s == "DynamicLookaheadConvexHullInserstion")
			return ConstructionType::DynamicLookaheadConvexHullInserstion;
		return ConstructionType::StaticLookaheadConvexHullInserstion;
	}

	static std::string runModeToName(const RunMode& r) {
		std::string name = jsonconversion::constructionTypeToString(r.Construction);
		if (r.Construction == ConstructionType::StaticLookahead ||
			r.Construction == ConstructionType::StaticLookaheadConvexHullInserstion)
			name += "(" + std::to_string(r.args.max_depth) + ")";
		return name;
	}

	static std::string optimisationTypeToString(OptimisationType o) {
		switch (o) {
			case OptimisationType::TwoOpt:
				return "TwoOpt";
			case OptimisationType::None:
				return "None";
			case OptimisationType::ThreeOpt:
				return "ThreeOpt";
		}
		return "N/A";
	}

	static OptimisationType stringToOptimisationType(const std::string& s) {
		if (s == "TwoOpt")
			return OptimisationType::TwoOpt;
		if (s == "None")
			return OptimisationType::None;
		if (s == "ThreeOpt")
			return OptimisationType::ThreeOpt;
		return OptimisationType::TwoOpt;
	}

	static std::string timeScaletoString(TimeScale t) {
		return std::to_string(t.count());
	}

	static TimeScale stringToTimeScale(const std::string& s) {
		return TimeScale(std::stoll(s));
	}

	static void point2DToJSON(const Point2D& p, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		v.SetObject();
		v.AddMember("x", p.m_x, a);
		v.AddMember("y", p.m_y, a);
	}

	static Point2D JSONToPoint2D(const rapidjson::Value& v) {
		return Point2D(v["x"].GetDouble(), v["y"].GetDouble());
	}

	static void squareToJSON(const Square& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		v.SetObject();
		
		rapidjson::Value p1;
		point2DToJSON(s.m_p1, p1, a);
		v.AddMember("p1", p1, a);

		rapidjson::Value p2;
		point2DToJSON(s.m_p2, p2, a);
		v.AddMember("p2", p2, a);
	}

	static Square JSONToSquare(const rapidjson::Value& v) {
		return Square(JSONToPoint2D(v["p1"]), JSONToPoint2D(v["p2"]));
	}

	static void TSPArgsToJson(const TSPArgs& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		v.SetObject();
		v.AddMember("num_threads", s.num_threads, a);
		v.AddMember("depth", s.max_depth, a);
		v.AddMember("timeout_ms", s.timeout_ms.count(), a);

		rapidjson::Value dynamic_args;
		dynamic_args.SetObject();
		dynamic_args.AddMember("logrithm", s.dynamic_args.logrithm, a);
		dynamic_args.AddMember("multiplier", s.dynamic_args.multiplier, a);
		dynamic_args.AddMember("constant", s.dynamic_args.constant, a);
		v.AddMember("dynamic_args", dynamic_args, a);

	}

	static void JsonToTSPArgs(TSPArgs& s, const rapidjson::Value& v) {
		s.num_threads = v["num_threads"].GetInt();
		s.max_depth = v["depth"].GetUint64();

		if (v.FindMember("timeout_ms") != v.MemberEnd())
			s.timeout_ms = std::chrono::milliseconds(v["timeout_ms"].GetInt64());
		else
			s.timeout_ms = std::chrono::milliseconds(v["timeout"].GetInt64());

		if (v.FindMember("dynamic_args") != v.MemberEnd()) {
			s.dynamic_args.logrithm = v["dynamic_args"]["logrithm"].GetDouble();
			s.dynamic_args.multiplier = v["dynamic_args"]["multiplier"].GetDouble();
			s.dynamic_args.constant = v["dynamic_args"]["constant"].GetDouble();
		}
	}

	static void runModeToJson(const RunMode& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		v.SetObject();
		v.AddMember("id", s.id, a);
		v.AddMember("num_cities", s.num_cities, a);
		addStringMember(v, "genType", GenerationTypeToString(s.genType), a);
		addStringMember(v, "Caching", cachingTypeToString(s.Caching), a);
		addStringMember(v, "Partitioning", partitioningTypeToString(s.Partitioning), a);
		addStringMember(v, "Construction", constructionTypeToString(s.Construction), a);
		addStringMember(v, "Optimisation", optimisationTypeToString(s.Optimisation), a);
		
		rapidjson::Value args;
		TSPArgsToJson(s.args, args, a);
		v.AddMember("args", args, a);
	}

	static void JsonToRunMode(RunMode& s, const rapidjson::Value& v) {
		s.id = v["id"].GetUint64();
		s.num_cities = v["num_cities"].GetUint64();
		s.genType = stringToGenerationType(v["genType"].GetString());
		s.Caching = stringToCachingType(v["Caching"].GetString());
		s.Partitioning = stringToPartitioningType(v["Partitioning"].GetString());
		s.Construction = stringToConstructionType(v["Construction"].GetString());
		s.Optimisation = stringToOptimisationType(v["Optimisation"].GetString());
		JsonToTSPArgs(s.args, v["args"]);
	}

	static void TSPResultToJson(const TSPResult& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		runModeToJson(s, v, a);
		
		rapidjson::Value val;
		squareToJSON(s.area, val, a);
		v.AddMember("area", val, a);
		
		v.AddMember("seed", s.seed, a);
		v.AddMember("constructTour_distance", s.constructTour_distance, a);
		v.AddMember("final_distance", s.final_distance, a);
		addStringMember(v, "validRoute", validityToString(s.validRoute), a);
		addStringMember(v, "total_run_time_us", timeScaletoString(s.total_run_time), a);
		addStringMember(v, "initalisePartition_time_us", timeScaletoString(s.initalisePartition_time), a);
		addStringMember(v, "initaliseCache_time_us", timeScaletoString(s.initaliseCache_time), a);
		addStringMember(v, "constructTour_time_us", timeScaletoString(s.constructTour_time), a);
		addStringMember(v, "optimiseTour_time_us", timeScaletoString(s.optimiseTour_time), a);
	}

	static void JsonToTSPResult(TSPResult& s, const rapidjson::Value& v) {
		JsonToRunMode(s, v);
		s.area = JSONToSquare(v["area"]);
		s.seed = v["seed"].GetUint();
		s.constructTour_distance = v["constructTour_distance"].GetDouble();
		s.final_distance = v["final_distance"].GetDouble();
		s.validRoute = stringToValidity(v["validRoute"].GetString());
		s.total_run_time = stringToTimeScale(v["total_run_time_us"].GetString());
		s.initalisePartition_time = stringToTimeScale(v["initalisePartition_time_us"].GetString());
		s.initaliseCache_time = stringToTimeScale(v["initaliseCache_time_us"].GetString());
		s.constructTour_time = stringToTimeScale(v["constructTour_time_us"].GetString());
		s.optimiseTour_time = stringToTimeScale(v["optimiseTour_time_us"].GetString());
	}

	static void TSPVerboseResultStaticToJson(const TSPVerboseResultStatic& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		TSPResultToJson(s, v, a);
		addStringMember(v, "name", s.name, a);
		addStringMember(v, "type", s.type, a);
		addStringMember(v, "comment", s.comment, a);
		addStringMember(v, "edge_weight_type", s.edge_weight_type, a);
		addStringMember(v, "display_data_type", s.display_data_type, a);
	}

	static void JsonToTSPVerboseResultStatic(TSPVerboseResultStatic& s, const rapidjson::Value& v) {
		JsonToTSPResult(s, v);
		s.name = v["name"].GetString();
		s.type = v["type"].GetString();
		s.comment = v["comment"].GetString();
		s.edge_weight_type = v["edge_weight_type"].GetString();
		s.display_data_type = v["display_data_type"].GetString();
	}

	static void TSPVerboseResultDynamicToJson(const TSPVerboseResultDynamic& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		TSPVerboseResultStaticToJson(s, v, a);

		rapidjson::Value node_coord_section;
		node_coord_section.SetArray();
		for (auto& p : s.node_coord_section) {
			rapidjson::Value point;
			point.SetObject();
			point2DToJSON(p.getPoint(), point, a);
			node_coord_section.PushBack(point, a);
		}
		v.AddMember("node_coord_section", node_coord_section, a);

		rapidjson::Value route;
		route.SetArray();
		for (auto& r : s.route) {
			route.PushBack(r, a);
		}
		v.AddMember("route", route, a);
	}

	static void JsonToTSPVerboseResultDynamic(TSPVerboseResultDynamic& s, const rapidjson::Value& v) {
		JsonToTSPVerboseResultStatic(s, v);

		s.node_coord_section.clear();
		for (auto& p : v["node_coord_section"].GetArray()) {
			s.node_coord_section.push_back(JSONToPoint2D(p));
		}

		s.route.clear();
		for (auto& r : v["route"].GetArray()) {
			s.route.push_back(r.GetUint64());
		}
	}

	static void StatisticEntryToJson(const StatisticEntry& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		v.SetObject();
		runModeToJson(s, v, a);
		v.AddMember("number_of_runs", s.number_of_runs, a);
		v.AddMember("number_of_valid_routes", s.number_of_valid_routes, a);
		v.AddMember("invalidRoutes", s.invalidRoutes, a);
		v.AddMember("timeouts", s.timeouts, a);
		v.AddMember("total_construct_tour_distance", s.total_construct_tour_distance, a);
		v.AddMember("total_final_distance", s.total_final_distance, a);
		addStringMember(v, "total_run_time_us", timeScaletoString(s.total_run_time), a);
		addStringMember(v, "total_initalisePartition_time_us", timeScaletoString(s.total_initalisePartition_time), a);
		addStringMember(v, "total_initaliseCache_time_us", timeScaletoString(s.total_initaliseCache_time), a);
		addStringMember(v, "total_constructTour_time_us", timeScaletoString(s.total_constructTour_time), a);
		addStringMember(v, "total_optimiseTour_time_us", timeScaletoString(s.total_optimiseTour_time), a);
	}

	static void JsonToStatisticEntry(StatisticEntry& s, const rapidjson::Value& v) {
		JsonToRunMode(s, v);
		s.number_of_runs = v["number_of_runs"].GetUint64();
		s.number_of_valid_routes = v["number_of_valid_routes"].GetUint64();
		s.invalidRoutes = v["invalidRoutes"].GetUint64();
		s.timeouts = v["timeouts"].GetUint64();
		s.total_construct_tour_distance = v["total_construct_tour_distance"].GetDouble();
		s.total_final_distance = v["total_final_distance"].GetDouble();
		s.total_run_time = stringToTimeScale(v["total_run_time_us"].GetString());
		s.total_initalisePartition_time = stringToTimeScale(v["total_initalisePartition_time_us"].GetString());
		s.total_initaliseCache_time = stringToTimeScale(v["total_initaliseCache_time_us"].GetString());
		s.total_constructTour_time = stringToTimeScale(v["total_constructTour_time_us"].GetString());
		s.total_optimiseTour_time = stringToTimeScale(v["total_optimiseTour_time_us"].GetString());
	}

	enum class JsonType {
		TSPResult,
		TSPVerboseResultStatic,
		TSPVerboseResultDynamic
	};

	static void resultToJson(const JsonType t, const TSPVerboseResultDynamic& s, rapidjson::Value& v, rapidjson::Document::AllocatorType& a) {
		v.SetObject();
		rapidjson::Value val;
		switch (t)
		{
			case jsonconversion::JsonType::TSPResult:
				addStringMember(v, "type", "TSPResult", a);
				TSPResultToJson(s, val, a);
				break;
			case jsonconversion::JsonType::TSPVerboseResultStatic:
				addStringMember(v, "type", "TSPVerboseResultStatic", a);
				TSPVerboseResultStaticToJson(s, val, a);
				break;
			case jsonconversion::JsonType::TSPVerboseResultDynamic:
				addStringMember(v, "type", "TSPVerboseResultDynamic", a);
				TSPVerboseResultDynamicToJson(s, val, a);
				break;
			default:
				break;
		}
		v.AddMember("object", val, a);
	}

	static void JsonToResult(const rapidjson::Value& v, TSPVerboseResultDynamic& s) {
		std::string type = v["type"].GetString();
		if (type == "TSPResult") {
			JsonToTSPResult(s, v["object"]);
		}
		else if (type == "TSPVerboseResultStatic") {
			JsonToTSPVerboseResultStatic(s, v["object"]);
		}
		else if (type == "TSPVerboseResultDynamic") {
			JsonToTSPVerboseResultDynamic(s, v["object"]);
		}
	}
}