#pragma once
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "../tsp_data/tsp_constructs.h"
#include "../tour_optimisation/optimisation_headers.h"
#include "../tour_construction/consturction_headers.h"
#include "timer.h"

enum Validity {	// TODO: This should be in tsp_output.h
	Valid,
	Invalid,
	Timeout
};

namespace jsonconversion {

	static std::string documentToString(const rapidjson::Document& doc) {
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		return buffer.GetString();
	}

	static std::string validityToString(Validity v) {
		switch (v) {
			case Valid:
				return "Valid";
			case Invalid:
				return "Invalid";
			case Timeout:
				return "Timeout";
		}
		return "N/A";
	}

	static Validity stringToValidity(const std::string& s) {
		if (s == "Valid")
			return Valid;
		if (s == "Invalid")
			return Invalid;
		if (s == "Timeout")
			return Timeout;
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
		return ConstructionType::StaticLookaheadConvexHullInserstion;
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
		return std::chrono::milliseconds(std::stoll(s));
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
}