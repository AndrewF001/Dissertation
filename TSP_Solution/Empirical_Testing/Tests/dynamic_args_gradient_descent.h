#pragma once
#include <gdcpp.h>
#include "test_class.h"
#include "basic_test.h"

class DynamicArgsGD : public TestClass {
public:
	DynamicArgsGD(size_t size, size_t ittr) : m_size(size), m_ittr(ittr), TestClass("DynamicArgsGD", false) {};
	~DynamicArgsGD() = default;

	void Test() override {
		_test<100>();
	};

private:
	size_t m_size;
    size_t m_ittr;

	template <size_t Size>
	void _test() {
		// Gradient Descent
        gdc::GradientDescent<double, DynamicArgsGDMethod<Size>,
			gdc::ConstantStepSize<double>> optimizer;

		// Settings
        optimizer.setMaxIterations(gdc::Index(m_ittr));
        optimizer.setMinGradientLength(0.00001);
        optimizer.setMinStepLength(0.00001);
        optimizer.setMomentum(0.4);
        optimizer.setVerbosity(4);

        optimizer.setStepSize(gdc::ConstantStepSize<double>(1));

        // Set initial guess.
		const DynamicArgs BASE;
        Eigen::VectorXd initialGuess(3);
        initialGuess << BASE.multiplier, BASE.logrithm, BASE.constant;

        // Start the optimization
        auto result = optimizer.minimize(initialGuess);

        std::cout << "Done! Converged: " << (result.converged ? "true" : "false")
            << " Iterations: " << result.iterations << std::endl;

        // do something with final x-value
		DynamicArgs d_args = { .multiplier = result.xval(0), .logrithm = result.xval(1), .constant = result.xval(2) };
		std::cout << "Final values, multiplier: " << d_args.multiplier << ", logrithm: " << d_args.logrithm << ", constant: " << d_args.constant << std::endl;
	}

	template <size_t Size>
	class DynamicArgsGDMethod
	{
	public:
		DynamicArgsGDMethod() {
			std::cout << "constructed" << std::endl;
			for (size_t i = 0; i < 5; i++)
				m_cities[i] = std::make_unique<std::array<Type2d, Size>>(Tester::generateCities<Size>(Tester::seed_gen()));
		};

		std::array<std::unique_ptr<std::array<Type2d, Size>>, 5> m_cities;

		double operator()(const Eigen::VectorXd& xval, Eigen::VectorXd&) const
		{
			double score = 0;

			assert(xval.size() == 3);
			DynamicArgs d_args = { .multiplier = xval(0), .logrithm = xval(1), .constant = xval(2) };
			TSPArgs args{ .max_depth = 8, .dynamic_args = d_args };

			std::cout << std::setprecision(17) << "ittr, multiplier: " << d_args.multiplier << ", logrithm: " << d_args.logrithm << ", constant: " << d_args.constant << std::endl;
			for (size_t i = 0; i < 5; i++) {
				auto algorithm = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::DynamicLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(AREA, *m_cities[i], GenerationType::rectangle, 0);
				score += algorithm->run(args).final_distance;
			}

			return score;
		}
	};
};
