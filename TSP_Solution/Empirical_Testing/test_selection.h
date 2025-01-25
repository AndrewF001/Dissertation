#pragma once
#include "Tests/basic_100_test.h"


namespace TSP_Selection {

	const size_t choiceSelect() {
		size_t input;
		std::cout << "Select test:\n";
		std::cout << "1. Basic 100\n";
		std::cin >> input;
		return input;
	}

	std::shared_ptr<TSPFile> menu(std::optional<size_t> choice, std::optional<size_t> ittr, bool use_file) {
		size_t input;

		while (!choice.has_value()) {
			choice = choiceSelect();
		}

		while (choice.value() < 1 || choice.value() > 1) {
			std::cout << "Invalid choice\n";
			choice = choiceSelect();
		}

		while(!ittr.has_value()) {
			std::cout << "Number of iterations: ";
			std::cin >> input;
			ittr = input;
		}

		switch (choice.value()) {
			case 1:
				Basic100Test test(use_file);
				return test.RunTests(ittr.value());
		}

		std::cout << "Invalid choice\n";
		return nullptr;
	}
}
