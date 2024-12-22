#pragma once
#include "tsp_output.h"
#include "file_handler.h"

class StatisticEntry {
	size_t number_of_runs;
	size_t number_of_valid_routes;
	size_t invalidRoutes;
	size_t timeouts;

	size_t num_cities;
	PartitioningType Partitioning;
	CachingType Caching;
	ConstructionType Construction;
	OptimisationType Optimisation;

	double total_construct_tour_distance;
	double total_final_distance;

	TimeScale total_run_time;
	TimeScale total_initalisePartition_time;
	TimeScale total_initaliseCache_time;
	TimeScale total_constructTour_time;
	TimeScale total_optimiseTour_time;
};

class TSPFile {
public:
	TSPFile(std::string path) : m_path(path) {
		//readFile();
	};

	void addEntry(const TSPVerboseResultDynamic& entry) {
		m_entries.push_back(entry);

		// Do statistics

		//writeFile();
	};

private:
	const std::string m_path;
	std::vector<StatisticEntry> m_statistics;
	std::vector<TSPVerboseResultStatic> m_entries;

	//const std::string FILEDIVEDER = "DOF";

	//void readFile() {
	//	auto probe = readFromFile(m_path);
	//	if (!probe.has_value())
	//		return;

	//	std::vector<uint8_t> file = probe.value();

	//	std::string file_str(file.begin(), file.end());
	//	size_t divider = file_str.find(FILEDIVEDER);
	//	if (divider == std::string::npos)
	//		throw std::invalid_argument("File is corrupt");

	//	uint8_t* statistics = file.data();
	//	uint8_t* entries = file.data() + divider + FILEDIVEDER.size();
	//	auto statistics_count = std::div((int)divider, sizeof(StatisticEntry));
	//	if (statistics_count.rem != 0)
	//		throw std::invalid_argument("File is corrupt");

	//	readStatistics(statistics, statistics_count.quot);
	//	readEntries(entries, &file.back());
	//};

	////void readStatistics(const std::string& statistics) {
	////	const char* statistics_ptr = statistics.c_str();
	////	for (size_t i = 0; i < statistics.size() / sizeof(StatisticEntry); i++) {
	////		m_statistics.push_back(stringToObject<StatisticEntry>(statistics_ptr));
	////		statistics_ptr += sizeof(StatisticEntry);
	////	}
	////};

	////void readEntries(const std::string& entries) {
	////	const char* entries_ptr = entries.c_str();
	////	while (entries_ptr != entries.c_str() + entries.size()) {
	////		TSPVerboseResultDynamic entry = stringToObject<TSPVerboseResultDynamic>(entries_ptr);
	////		entries_ptr += sizeof(TSPVerboseResultDynamic);

	////		//entry.node_coord_section = std::vector<Point2D>(entry.num_cities);
	////		for (size_t i = 0; i < 100; i++) {
	////			entry.node_coord_section.push_back(stringToObject<Point2D>(entries_ptr));
	////			entries_ptr += sizeof(Point2D);
	////		}

	////		//entry.route = std::vector<cityID>(entry.num_cities + 1);
	////		for (size_t i = 0; i < 101; i++) {
	////			entry.route.push_back(stringToObject<cityID>(entries_ptr));
	////			entries_ptr += sizeof(cityID);
	////		}
	////		m_entries.push_back(entry);
	////	}
	////}


	//void readStatistics(uint8_t* statistics, size_t number) {
	//	for (size_t i = 0; i < number; i++) {
	//		m_statistics.push_back(bytesToObject<StatisticEntry>(statistics));
	//		statistics += sizeof(StatisticEntry);
	//	}
	//};

	//void readEntries(uint8_t* entries, uint8_t* end) {
	//	
	//	while (entries != end) {
	//		TSPVerboseResultStatic entry = bytesToObject<TSPVerboseResultStatic>(entries);
	//		entries += sizeof(TSPVerboseResultDynamic);

	//		//entry.node_coord_section = std::vector<Point2D>(entry.num_cities);
	//		//entry.node_coord_section = std::vector<Point2D>();
	//		//for (size_t i = 0; i < 100; i++) {
	//		//	entry.node_coord_section.push_back(bytesToObject<Point2D>(entries));
	//		//	entries += sizeof(Point2D);
	//		//}

	//		////entry.route = std::vector<cityID>(entry.num_cities + 1);
	//		//entry.route = std::vector<cityID>();
	//		//for (size_t i = 0; i < 101; i++) {
	//		//	entry.route.push_back(bytesToObject<cityID>(entries));
	//		//	entries += sizeof(cityID);
	//		//}
	//		m_entries.push_back(entry);
	//	}
	//}


	//void writeFile() {
	//	std::string file = "";
	//	for (const auto& stat : m_statistics) {
	//		file += objectToString<StatisticEntry>(&stat);
	//	}

	//	file += FILEDIVEDER;

	//	for (const auto& entry : m_entries) {
	//		file += objectToString<TSPVerboseResultStatic>(&entry);
	//		//for (const auto& point : entry.node_coord_section) {
	//		//	file += objectToString<Point2D>(&point);
	//		//}
	//		//for (const auto& city : entry.route) {
	//		//	file += objectToString<cityID>(&city);
	//		//}
	//	}

	//	writeToFile(m_path, file);
	//};
};