#pragma once
#include "Tests/basic_test.h"


namespace TSP_Selection {

	const size_t choiceSelect() {
		size_t input;
		std::cout << "Select test:\n";
		std::cout << "1. Basic 100\n";
		std::cout << "2. Basic 200\n";
		std::cout << "3. Basic 500\n";
		std::cout << "4. Basic 1000\n";
		std::cout << "5. Basic 2000\n";
		std::cout << "6. Basic 3000\n";
		std::cout << "7. Basic 4000\n";
		std::cout << "8. Basic 5000\n";

		std::cin >> input;
		return input;
	}

	std::shared_ptr<TSPFile> menu(std::optional<size_t> choice, std::optional<size_t> ittr, bool use_file) {
		size_t input;

		while (!choice.has_value()) {
			choice = choiceSelect();
		}

		while (choice.value() < 1 || choice.value() > 8) {
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
		{
			BasicTest<100> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 2:
		{
			BasicTest<200> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 3:
		{
			BasicTest<500> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 4:
		{
			BasicTest<1000> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 5:
		{
			BasicTest<2000> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 6:
		{
			BasicTest<3000> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 7:
		{
			BasicTest<4000> test(use_file);
			return test.RunTests(ittr.value());
		}
		case 8:
		{
			BasicTest<5000> test(use_file);
			return test.RunTests(ittr.value());
		}
		}

		std::cout << "Invalid choice\n";
		return nullptr;
	}
}
