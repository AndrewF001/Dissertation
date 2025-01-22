#include <iostream>
#include <file_handling/tsp_file.h>

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

int main() {
	auto file = readFile();
}

