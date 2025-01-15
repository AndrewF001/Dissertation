#pragma once
#include "tsp_output.h"
#include "file_handler.h"
#include "json_convertion.h"

class TSPFile {
public:
	TSPFile(std::string path) : m_path(path.append(FILEEXTENSION)) {
		readFile();
		//m_statisticsArray = m_doc["statistics"].GetArray();
		//m_entriesArray = m_doc["entries"].GetArray();
	};

	void addEntry(TSPVerboseResultDynamic& entry) {
		entry.id = m_entries.size();
		m_entries.push_back(entry);

		rapidjson::Value v;
		jsonconversion::TSPVerboseResultDynamicToJson(entry, v, m_doc.GetAllocator());
		m_doc["entries"].GetArray().PushBack(v, m_doc.GetAllocator());

		updateStatistics(entry);	// TODO: This need to update m_doc
	};

	void writeFile() {
		_writeFile();
	};

private:
	const std::string FILEEXTENSION = ".mytsp";
	const char* N_STATISTICS = "statistics";
	const char* N_ENTRIES = "entries";

	const std::string m_path;
	std::vector<StatisticEntry> m_statistics;
	std::vector<TSPVerboseResultDynamic> m_entries;
	rapidjson::Document m_doc;
	//rapidjson::GenericArray<false, rapidjson::Value> m_statisticsArray;
	//rapidjson::GenericArray<false, rapidjson::Value> m_entriesArray;

	void readFile() {
		auto file = readFromFile(m_path);

		if (!file.has_value()) {
			Logger::log("File not found: " + m_path);
			createBlankDoc();
			return;
		}

		m_doc = jsonconversion::stringToDocument(file.value());
		m_doc.IsObject();

		if (m_doc.HasParseError())
			throw std::runtime_error("Error parsing file: " + m_path);

		if (!m_doc.HasMember(N_STATISTICS) && !m_doc[N_STATISTICS].IsArray())
			throw std::runtime_error("Error parsing Statistics array: " + m_path);

		if (!m_doc.HasMember(N_ENTRIES) && !m_doc[N_ENTRIES].IsArray())
			throw std::runtime_error("Error parsing Entries array: " + m_path);

		readStatistics(m_doc[N_STATISTICS]);
		readEntries(m_doc[N_ENTRIES]);
	};

	void readStatistics(const rapidjson::Value& v) {
		for (auto& s : v.GetArray()) {
			StatisticEntry entry{};
			jsonconversion::JsonToStatisticEntry(entry, s);
			m_statistics.push_back(entry);
		}
	};

	void readEntries(const rapidjson::Value& v) {
		for (auto& s : v.GetArray()) {
			TSPVerboseResultDynamic entry{};
			jsonconversion::JsonToTSPVerboseResultDynamic(entry, s);
			m_entries.push_back(entry);
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
			newEntry.id = m_statistics.size();

			m_statistics.push_back(newEntry);
			m_doc[N_STATISTICS].GetArray().PushBack(rapidjson::Value(), m_doc.GetAllocator());
			
			entry = &m_statistics.back();
		}

		entry->append(data);
		jsonconversion::StatisticEntryToJson(*entry, m_doc[N_STATISTICS].GetArray()[entry->id], m_doc.GetAllocator());
	};

	void _writeFile() {
		auto file = jsonconversion::documentToString(m_doc);
		writeToFile(m_path, file);
	};

    void createBlankDoc() {
        m_doc.SetObject();
        
        // Add a new line break
        rapidjson::Value val;
        val.SetArray();
        m_doc.AddMember("statistics", val, m_doc.GetAllocator());

        rapidjson::Value val2;
        val2.SetArray();
        m_doc.AddMember("entries", val2, m_doc.GetAllocator());
    }
};