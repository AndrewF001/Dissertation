#pragma once


// This file is used to store the sizes of the TSPLib files
// It also has code that turns the array into an std::index_sequence
// This is needed for compile time iteration over the sizes
// Look into tsplib_test.h selectOne() for an example of how to use this
namespace tsplib {

	template<const auto& A,
		class = std::make_index_sequence<
		std::tuple_size<std::decay_t<decltype(A)>>::value>>
		struct as_sequence;
	template<const auto& A, std::size_t ...II>
	struct as_sequence<A, std::index_sequence<II...>> {
		using type = std::integer_sequence<
			typename std::decay_t<decltype(A)>::value_type, A[II]...>;
	};

	constexpr std::array<size_t, 95> SIZES = { 14,16,17,21,22,24,26,29,42,48,51,52,58,70,76,96,99,100,101,105,107,120,124,127,130,136,137,144,150,152,159,175,180,195,198,200,202,225,226,229,262,264,280,299,318,400,417,431,439,442,493,532,535,561,574,575,654,657,666,724,783,1000,1002,1032,1060,1084,1173,1291,1304,1323,1379,1400,1432,1577,1655,1748,1817,1889,2103,2152,2319,2392,3038,3795,4461,5915,5934,7397,11849,13509,14051,15112,18512,33810,85900 };
	using SIZES_seq = as_sequence<tsplib::SIZES>::type;
}