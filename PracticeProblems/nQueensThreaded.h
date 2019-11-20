#include "pch.h"
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <iostream>
#include <deque>

namespace cpioli {
	void shared_printer(std::vector<std::string> &board);
	void solveNQueensConcurrently(uint64_t n);
	void threadRequestTask(std::vector<std::string> board, uint64_t& n);
	void beginTask(std::vector<std::string> &board,
		uint64_t &colMask,
		uint64_t &deg45Mask,
		uint64_t &deg135Mask,
		uint64_t &n,
		uint64_t row);
}
