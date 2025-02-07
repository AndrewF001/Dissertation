#pragma once
#include "Tests/basic_test.h"
#include "Tests/multi_test.h"
#include "Tests/dynamic_test.h"
#include "Tests/dynamic_args_refined.h"


namespace TSP_Selection {
	const size_t choiceSelect() {
		size_t input;
		std::cout << "Select test:\n";
		std::cout << "1. Basic\n";
		std::cout << "2. Multi\n";
		std::cout << "3. Dynamic\n";
		std::cout << "4. DynamicArgs\n";
		std::cout << "5. TSPlib\n";

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
		for (size_t i = 0; i < SIZES.size(); i++) {
			std::cout << i + 1 << ". " << SIZES[i] << "\n";
		}
		std::cin >> input;
		return input;
	}

	std::shared_ptr<TSPFile> MultiTestRun(size_t size, size_t ittr, bool use_file) {
		auto tester = std::make_unique<MultiTest>(use_file, size);
		return tester->RunTests(ittr);
	}

	std::shared_ptr<TSPFile> DynamicTestRun(size_t size, size_t ittr, bool use_file) {
		auto tester = std::make_unique<DynamicTest>(use_file, size);
		return tester->RunTests(ittr);
	}

	std::shared_ptr<TSPFile> DynamicArgsTestRun(size_t size, size_t ittr, bool use_file) {
		auto tester = std::make_unique<DynamicArgsTest>(use_file, size);
		return tester->RunTests(ittr);
	}

	std::shared_ptr<TSPFile> BasicTestRun(size_t size, size_t ittr, bool use_file) {
		switch (size) {
			case 1:
			{
				auto tester = std::make_unique<BasicTest<SIZES[0], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 2:
			{
				auto tester = std::make_unique<BasicTest<SIZES[1], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 3:
			{
				auto tester = std::make_unique<BasicTest<SIZES[2], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 4:
			{
				auto tester = std::make_unique<BasicTest<SIZES[3], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 5:
			{
				auto tester = std::make_unique<BasicTest<SIZES[4], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 6:
			{
				auto tester = std::make_unique<BasicTest<SIZES[5], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 7:
			{
				auto tester = std::make_unique<BasicTest<SIZES[6], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 8:
			{
				auto tester = std::make_unique<BasicTest<SIZES[7], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 9:
			{
				auto tester = std::make_unique<BasicTest<SIZES[8], OptimisationType::TwoOpt>>(use_file);
				return tester->RunTests(ittr);
			}
			case 10:
			{
				auto tester = std::make_unique<BasicTest<SIZES[9], OptimisationType::TwoOpt>>(use_file);
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

		while (choice.value() < 1 || choice.value() > 5) {
			std::cout << "Invalid choice\n";
			choice = choiceSelect();
		}

		if (choice.value() != 5 ) {
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
				return MultiTestRun(size.value(), ittr.value(), use_file);
			case 3:
				return DynamicTestRun(size.value(), ittr.value(), use_file);
			case 4:
				return DynamicArgsTestRun(size.value(), ittr.value(), use_file);
			case 5:
				//return TSPLibTestRun(use_file);
				break;
			
		}

		std::cout << "Invalid choice\n";
		return nullptr;
	}
}
