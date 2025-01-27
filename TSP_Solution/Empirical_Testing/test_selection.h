#pragma once
#include "Tests/basic_test.h"


namespace TSP_Selection {

	constexpr std::array<size_t, 10> sizes{ 10, 100, 200, 300, 500, 1000, 2000, 3000, 4000, 5000 };

	const size_t choiceSelect() {
		size_t input;
		std::cout << "Select test:\n";
		std::cout << "1. Basic\n";
		std::cout << "2. Multi\n";
		std::cout << "3. TSPlib\n";

		std::cin >> input;
		return input;
	}

	const size_t sizeSelect(size_t size) {
		size_t input;
		if (size == 1) {
			std::cout << "Select size:\n";
		}
		else {
			std::cout << "Select max size:\n";
		}
		for (size_t i = 0; i < sizes.size(); i++) {
			std::cout << i + 1 << ". " << sizes[i] << "\n";
		}
		std::cin >> input;
		return input;
	}

	std::shared_ptr<TSPFile> BasicTestRun(size_t size, size_t ittr, bool use_file) {
		switch (size) {
			case 1:
			{
				auto tester = std::make_unique<BasicTest<sizes[0], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 2:
			{
				auto tester = std::make_unique<BasicTest<sizes[1], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 3:
			{
				auto tester = std::make_unique<BasicTest<sizes[2], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 4:
			{
				auto tester = std::make_unique<BasicTest<sizes[3], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 5:
			{
				auto tester = std::make_unique<BasicTest<sizes[4], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 6:
			{
				auto tester = std::make_unique<BasicTest<sizes[5], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 7:
			{
				auto tester = std::make_unique<BasicTest<sizes[6], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 8:
			{
				auto tester = std::make_unique<BasicTest<sizes[7], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 9:
			{
				auto tester = std::make_unique<BasicTest<sizes[8], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 10:
			{
				auto tester = std::make_unique<BasicTest<sizes[9], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
		}
		return nullptr;
	}

	std::shared_ptr<TSPFile> menu(std::optional<size_t> choice, std::optional<size_t> size, std::optional<size_t> ittr, bool use_file) {
		size_t input;

		while (!choice.has_value()) {
			choice = choiceSelect();
		}

		while (choice.value() < 1 || choice.value() > 3) {
			std::cout << "Invalid choice\n";
			choice = choiceSelect();
		}

		if (choice.value() != 3 ) {
			if (!size.has_value())
				size = sizeSelect(choice.value());

			while (!ittr.has_value()) {
				std::cout << "Number of iterations: ";
				std::cin >> input;
				ittr = input;
			}
		}

		switch (choice.value()) {
			case 1:
				return BasicTestRun(size.value(), ittr.value(), use_file);
				
			case 2:
				//return MultiTestRun(size, ittr, use_file);
				break;
			case 3:
				//return TSPLibTestRun(use_file);
				break;
			
		}

		std::cout << "Invalid choice\n";
		return nullptr;
	}
}
