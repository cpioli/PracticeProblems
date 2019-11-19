#include "pch.h"
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <iostream>
#include <deque>

namespace cpioli {
	void concurrentHelper(//vector<vector<string>> &answers,
		std::vector<std::string> &board,
		uint64_t &colMask,
		uint64_t &deg45Mask,
		uint64_t &deg135Mask,
		uint64_t &n,
		uint64_t row);

	void threadedHelper(//vector<vector<string>> answers,
		std::vector<std::string> board,
		uint64_t colMask,
		uint64_t deg45Mask,
		uint64_t deg135Mask,
		uint64_t n);

	void thread_func();

	void solveNQueensConcurrently(uint64_t n);

	void shared_printer(std::vector<std::string> &board);
}
