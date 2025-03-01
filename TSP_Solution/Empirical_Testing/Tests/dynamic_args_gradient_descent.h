#pragma once
#include <gsl/gsl_multimin.h>
#include "test_class.h"
#include "basic_test.h"
#include "file_handler.h"

namespace DAGD {

	constexpr size_t NUMOFPROBLEMS = 5;

	template <size_t Size>
	double cost_function(const gsl_vector* v, void* params) {
		double score = 0;
		std::array<std::unique_ptr<std::array<Type2d, Size>>, NUMOFPROBLEMS>* m_cities = (std::array<std::unique_ptr<std::array<Type2d, Size>>, NUMOFPROBLEMS>*)params;
		DynamicArgs d_args = { .multiplier = gsl_vector_get(v, 0), .logrithm = gsl_vector_get(v, 1), .constant = gsl_vector_get(v, 2) };
		TSPArgs args{ .max_depth = 10, .timeout_ms = std::chrono::milliseconds(300000), .dynamic_args = d_args};

		//std::cout << std::setprecision(17) << "ittr, multiplier: " << d_args.multiplier << ", logrithm: " << d_args.logrithm << ", constant: " << d_args.constant << std::endl;
		for (size_t i = 0; i < NUMOFPROBLEMS; i++) {
			auto algorithm = std::make_unique<TspTemplate<Type2d, Size, CachingType::full, PartitioningType::quadTree, ConstructionType::DynamicLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(AREA, *((*m_cities)[i]), GenerationType::rectangle, 0);
			score += algorithm->run(args).final_distance;
		}

		return score;
	}

	class DynamicArgsGD : public TestClass {
	public:
		DynamicArgsGD(size_t size, size_t ittr) : m_size(size), m_ittr(ittr), TestClass("DynamicArgsGD", false) {};
		~DynamicArgsGD() = default;

		void Test() override {
			if (m_size == 0)
				_test<SIZES[0]>();
			if (m_size == 1)
				_test<SIZES[1]>();
			if (m_size == 2)
				_test<SIZES[2]>();
			if (m_size == 3)
				_test<SIZES[3]>();
			if (m_size == 4)
				_test<SIZES[4]>();
			if (m_size == 5)
				_test<SIZES[5]>();
			if (m_size == 6)
				_test<SIZES[6]>();
			if (m_size == 7)
				_test<SIZES[7]>();
			if (m_size == 8)
				_test<SIZES[8]>();
			if (m_size == 9)
				_test<SIZES[9]>();
		};

	private:
		size_t m_size;
		size_t m_ittr;
		//std::array<std::unique_ptr<std::array<Type2d, Size>>, 5> m_cities;

		template <size_t Size>
		void _test() {
			std::array<std::unique_ptr<std::array<Type2d, Size>>, NUMOFPROBLEMS> m_cities;
			for (size_t i = 0; i < NUMOFPROBLEMS; i++)
				m_cities[i] = std::make_unique<std::array<Type2d, Size>>(Tester::generateCities<Size>(Tester::seed_gen()));

			// 1. Initialize the minimizer
			const gsl_multimin_fminimizer_type* T = gsl_multimin_fminimizer_nmsimplex2;
			gsl_multimin_fminimizer* s = gsl_multimin_fminimizer_alloc(T, 3);

			// 2. Set initial guess (starting point)
			DynamicArgs BASE;
			gsl_vector* args_vec = gsl_vector_alloc(3);
			gsl_vector_set(args_vec, 0, BASE.multiplier);
			gsl_vector_set(args_vec, 1, BASE.logrithm);
			gsl_vector_set(args_vec, 2, BASE.constant);

			// 3. Set step size for the simplex method
			gsl_vector* step_size = gsl_vector_alloc(3);
			gsl_vector_set_all(step_size, 0.001); // Small step sizes

			// 4. Define the minimization function
			gsl_multimin_function min_func;
			min_func.n = 3;
			min_func.f = cost_function<Size>;
			min_func.params = &m_cities;

			// 5. Initialize minimizer with function, initial guess, and step size
			gsl_multimin_fminimizer_set(s, &min_func, args_vec, step_size);

			// 6. Iteratively minimize the function
			int iter = 0, status;
			do {
				iter++;
				status = gsl_multimin_fminimizer_iterate(s);

				if (status) break; // Stop if there's an error

				double size = gsl_multimin_fminimizer_size(s);
				status = gsl_multimin_test_size(size, 1e-6);

				std::stringstream res;
				res << std::setprecision(17) << "multiplier=" << gsl_vector_get(s->x, 0)
					<< ", logirtihm=" << gsl_vector_get(s->x, 1)
					<< ", constant=" << gsl_vector_get(s->x, 2);

				std::cout << "Iteration " << iter << ": " << res.str() << ", size=" << size << "\n";

				FileHandler::writeToFile("DAGS.data", res.str());
			} while (status == GSL_CONTINUE && iter < m_ittr);

			// 7. Output optimized values
			std::cout << "Optimized variables: x=" << gsl_vector_get(s->x, 0)
				<< ", y=" << gsl_vector_get(s->x, 1)
				<< ", z=" << gsl_vector_get(s->x, 2) << "\n";

			// 8. Cleanup
			gsl_vector_free(args_vec);
			gsl_vector_free(step_size);
			gsl_multimin_fminimizer_free(s);
		}
	};
}
