#include <iostream>
#include <file_handling/tsp_file.h>
#include <tsp_template.h>

static std::unique_ptr<TSPFile> readFile() {
	std::string file_path;
	
	std::unique_ptr<TSPFile> file;

	do {
		std::cout << "Enter the file path: ";	// TODO: make this a Windows Explorer file dialog
		std::cin >> file_path;

		if (TSPFile::FILEEXTENSION.size() <= file_path.size()) {
			if (!file_path.compare(file_path.size() - TSPFile::FILEEXTENSION.size(), TSPFile::FILEEXTENSION.size(), TSPFile::FILEEXTENSION))
				file_path.erase(file_path.size() - TSPFile::FILEEXTENSION.size());
		}

		file = std::make_unique<TSPFile>(file_path);
	} while (!file->completedReadFile());

	return file;
}

static int menu() {
	int output;
	
	std::cout << "menu" << std::endl;
	std::cout << "1. Replay entry id" << std::endl;
	std::cout << "2. Failed runs" << std::endl;
	std::cin >> output;

	return output;
}


static void replayRun(const TSPVerboseResultDynamic& entry) {
	//auto cities = entry.node_coord_section;

	// TODO: THIS IS THE PROBLEM WITH TEMPLATES!
	//TspTemplate<
	//	Type2d,
	//	entry.num_cities,
	//	entry.Caching,
	//	entry.Partitioning,
	//	entry.Construction,
	//	entry.Optimisation
	//>tsp(entry.area,cities, entry.genType, entry.seed);area, cities, GenerationType::rectangle, seed
	
	std::array<Type2d, 100> cities;
	std::copy_n(entry.node_coord_section.begin(), 100, cities.begin());

	TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>tsp(entry.area, cities, entry.genType, entry.seed);
	tsp.run(entry.args);
}

static void replay(const TSPFile& file) {
	size_t id;
	std::cout << "Enter the entry id: ";
	std::cin >> id;

	if (id >= file.getEntries().size()) {
		std::cout << "Invalid entry id" << std::endl;
		return;
	}

	replayRun(file.getEntries()[id]);
}

static void failedRuns(const TSPFile& file) {
	auto entries = file.getEntries();

	for (auto& entry : entries) {
		if (entry.validRoute != Invalid)
			continue;

		std::cout << "Replaying failed run: " << entry.id << std::endl;
	}
}

int main() {
	auto file = readFile();

	
	while (true) {

		auto option = menu();

		switch (option) {
			case 1:
				replay(*file);
				break;
			case 2:
				failedRuns(*file);
				break;
			default:
				return 0;
		}
	}

	return 0;
}

