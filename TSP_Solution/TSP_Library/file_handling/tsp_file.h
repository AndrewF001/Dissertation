#pragma once
#include "tsp_structs.h"
#include "file_handler.h"
#include "json_convertion.h"

//class TSPFile;	// Forward declaration
//
//#include "ExcelCreator.h"


class TSPFile {
public:
	inline static const std::string FILEEXTENSION = ".mytsp";
	const std::string m_name;

	TSPFile(std::string path, jsonconversion::JsonType type = jsonconversion::JsonType::TSPResult) : m_name(path), m_type(type)  {
		m_completedReadFile = readFile();
	};

	void addEntry(TSPVerboseResultDynamic&& entry) {
		entry.id = m_entries.size();
		m_entries.emplace_back(entry);

		rapidjson::Value v;
		if (entry.validRoute == Invalid)	
			jsonconversion::resultToJson(jsonconversion::JsonType::TSPVerboseResultDynamic, entry, v, m_doc.GetAllocator());
		else 
			jsonconversion::resultToJson(m_type, entry, v, m_doc.GetAllocator());


		m_doc[N_ENTRIES].GetArray().PushBack(v, m_doc.GetAllocator());

		updateStatistics(entry);
	};

	// Avoid using this one
	void addEntryCopy(TSPVerboseResultDynamic entry) {
		entry.id = m_entries.size();
		m_entries.emplace_back(entry);

		rapidjson::Value v;
		if (entry.validRoute == Invalid)
			jsonconversion::resultToJson(jsonconversion::JsonType::TSPVerboseResultDynamic, entry, v, m_doc.GetAllocator());
		else
			jsonconversion::resultToJson(m_type, entry, v, m_doc.GetAllocator());


		m_doc[N_ENTRIES].GetArray().PushBack(v, m_doc.GetAllocator());

		updateStatistics(entry);
	}

	void writeFile() {
		_writeFile();
	};

	bool completedReadFile() const {
		return m_completedReadFile;
	};

	const std::vector<StatisticEntry>& getStatistics() const {
		return m_statistics;
	};

	const std::vector<TSPVerboseResultDynamic>& getEntries() const {
		return m_entries;
	};

	void mergeFiles(const TSPFile& file) {
		for (const auto& entry : file.getEntries()) {
			addEntryCopy(entry);	// Has to copy each one 
		}
	};

	//void createExcel() const {
	//	ExcelCreator::createExcel(*this);
	//}

private:
	inline static const char* N_STATISTICS = "statistics";
	inline static const char* N_ENTRIES = "entries";


	std::vector<StatisticEntry> m_statistics;
	std::vector<TSPVerboseResultDynamic> m_entries;

	bool m_completedReadFile = false;
	jsonconversion::JsonType m_type;
	rapidjson::Document m_doc;

	bool readFile() {
		auto file = FileHandler::readFromFile(m_name + FILEEXTENSION);

		if (!file.has_value()) {
			Logger::log("File not found: " + m_name + "\n", 0);
			createBlankDoc();
			return false;
		}

		m_doc = jsonconversion::stringToDocument(file.value());

		if (m_doc.HasParseError()) {
			Logger::error("Error parsing file: " + m_name + "\n");
			return false;	// Can't do the next checks
		}

		if (!m_doc.IsObject()) {
			Logger::error("Error File isn't a JSON object: " + m_name + "\n");
			return false;
		};

		if (!m_doc.HasMember(N_STATISTICS) && !m_doc[N_STATISTICS].IsArray()) {
			Logger::error("Error parsing Statistics array: " + m_name + "\n");
			return false;
		}

		if (!m_doc.HasMember(N_ENTRIES) && !m_doc[N_ENTRIES].IsArray()) {
			Logger::error("Error parsing Entries array: " + m_name + "\n");
			return false;
		}

		readStatistics(m_doc[N_STATISTICS]);
		readEntries(m_doc[N_ENTRIES]);

		return true;
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
			jsonconversion::JsonToResult(s, entry);
			m_entries.emplace_back(std::move(entry));
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
		jsonconversion::StatisticEntryToJson(*entry, m_doc[N_STATISTICS].GetArray()[rapidjson::SizeType(entry->id)], m_doc.GetAllocator());
	};

	void _writeFile() {
		auto file = jsonconversion::documentToString(m_doc);
		FileHandler::writeToFile(m_name + FILEEXTENSION, file);
	};

    void createBlankDoc() {
        m_doc.SetObject();
        
        // Add a new line break
        rapidjson::Value val;
        val.SetArray();
        m_doc.AddMember(rapidjson::Value(N_STATISTICS, m_doc.GetAllocator()), val, m_doc.GetAllocator());

        rapidjson::Value val2;
        val2.SetArray();
        m_doc.AddMember(rapidjson::Value(N_ENTRIES, m_doc.GetAllocator()), val2, m_doc.GetAllocator());
    }
};