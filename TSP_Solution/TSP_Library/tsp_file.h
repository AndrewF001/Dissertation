#pragma once
#include "tsp_output.h"
#include "file_handler.h"

class TSPFile {
public:
	TSPFile(std::string path) : m_path(path.append(FILEEXTENSION)) {
		readFile();
	};

	void addEntry(const TSPVerboseResultDynamic& entry) {
		m_entries.push_back(entry);
		updateStatistics(entry);
	};

	void writeFile() {
		std::string file = "";
		for (const auto& stat : m_statistics) {
			file += objectToString<StatisticEntry>(&stat);
		}

		file += FILEDIVEDER;

		for (const auto& entry : m_entries) {
			file += objectToString<TSPResult>(&entry);
			//for (const auto& point : entry.node_coord_section) {
			//	file += objectToString<Point2D>(&point);
			//}
			//for (const auto& city : entry.route) {
			//	file += objectToString<cityID>(&city);
			//}
		}
		writeToFile(m_path, file);
	};

private:
	const std::string m_path;
	std::vector<StatisticEntry> m_statistics;
	std::vector<TSPResult> m_entries;

	const static std::string FILEDIVEDER;
	const static std::string FILEEXTENSION;

	void readFile() {
		auto probe = readFromFile(m_path);
		if (!probe.has_value())
			return;

		std::string file = probe.value();

		size_t divider = file.find(FILEDIVEDER);
		if (divider == std::string::npos)
			throw std::invalid_argument("File is corrupt");

		std::string statistics = file.substr(0,divider);
		std::string entries = file.substr(divider + FILEDIVEDER.size());

		if (statistics.size() % sizeof(StatisticEntry) != 0)
			throw std::invalid_argument("File is corrupt");

		auto k = entries.size() - 1;
		auto s = sizeof(TSPResult);
		auto t = k % s;

		if (t != 0)
			throw std::invalid_argument("File is corrupt");

		readStatistics(statistics);
		readEntries(entries);
	};

	void readStatistics(const std::string& statistics) {
		const char* statistics_ptr = statistics.c_str();
		for (size_t i = 0; i < statistics.size() / sizeof(StatisticEntry); i++) {
			m_statistics.push_back(stringToObject<StatisticEntry>(statistics_ptr));
			statistics_ptr += sizeof(StatisticEntry);
		}
	};

	void readEntries(const std::string& entries) {
		const char* entries_ptr = entries.c_str();
		for (size_t i = 0; i < entries.size() / sizeof(TSPResult); i++) {
			m_entries.push_back(stringToObject<TSPResult>(entries_ptr));
			entries_ptr += sizeof(TSPResult);

			////entry.node_coord_section = std::vector<Point2D>(entry.num_cities);
			//for (size_t i = 0; i < 100; i++) {
			//	entry.node_coord_section.push_back(stringToObject<Point2D>(entries_ptr));
			//	entries_ptr += sizeof(Point2D);
			//}

			////entry.route = std::vector<cityID>(entry.num_cities + 1);
			//for (size_t i = 0; i < 101; i++) {
			//	entry.route.push_back(stringToObject<cityID>(entries_ptr));
			//	entries_ptr += sizeof(cityID);
			//}
			//m_entries.push_back(entry);
		}
	}

	void updateStatistics(const TSPVerboseResultDynamic& data) {
		StatisticEntry* entry = nullptr;

		for (size_t i = 0; i < m_statistics.size(); i++) {
			if (m_statistics[i] == data) {
				entry = &m_statistics[i];
				break;
			}
		}

		if (entry == nullptr) {
			StatisticEntry newEntry{};

			newEntry.set(data);

			m_statistics.push_back(newEntry);
			entry = &m_statistics.back();
		}

		entry->append(data);
	};

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
};

const std::string TSPFile::FILEDIVEDER = "DOF";
const std::string TSPFile::FILEEXTENSION = ".tsp1";