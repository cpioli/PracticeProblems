#include "pch.h"
#include "nQueensThreaded.h"

namespace cpioli {
	std::deque < std::packaged_task<void(void)> > helperQueue;
	std::mutex queueMu;
	std::mutex printMu;

	void shared_printer(std::vector<std::string> &board) {
		std::lock_guard<std::mutex> lock(printMu);
		for (int i = board.size() - 1; i > 0; i--)
			std::cout << board[i] << std::endl;
		std::cout << std::endl;
	}

	void concurrentHelper(//vector<vector<string>> &answers,
		std::vector<std::string> &board,
		uint64_t &colMask,
		uint64_t &deg45Mask,
		uint64_t &deg135Mask,
		uint64_t &n,
		uint64_t row) {

		if (row == n) {
			shared_printer(board);
			return;
		}
		for (uint64_t col = 0; col < n; col++) {

			if (!(colMask & (uint64_t)1 << col)
				&& !(deg45Mask & (uint64_t)1 << (row + col))
				&& !(deg135Mask & (uint64_t)1 << (n - 1 + row - col))
				) {
				colMask ^= 1LL << col;
				deg45Mask ^= 1LL << (row + col);
				deg135Mask ^= 1LL << (n - 1 + row - col);
				board[row][col] = 'Q';
				concurrentHelper(board, colMask, deg45Mask, deg135Mask, n, row + 1);
				board[row][col] = '.';
				colMask ^= 1LL << col;
				deg45Mask ^= 1LL << (row + col);
				deg135Mask ^= 1LL << (n - 1 + row - col);
			}
		}
	}

	//I THINK THE ISSUE IS PASSING A VARIABLE BY REFERENCE INTO A BOUND FUNCTION
	//INSTEAD I SHOULD PASS-BY-VALUE INTO threadedHelper, AND THEN threadedHelper
	//PASSES THE VALUES BY-REFERENCE INTO THE RECURSIVE FUNCTION helper!

	void threadedHelper(//vector<vector<string>> answers,
		std::vector<std::string> board,
		//vector<uint64_t> queens,
		uint64_t colMask,
		uint64_t deg45Mask,
		uint64_t deg135Mask,
		uint64_t n) {

		concurrentHelper(board, colMask, deg45Mask, deg135Mask, n, 1);

	}

	void thread_func() {
		std::packaged_task<void()> t;

		while (true) {
			{
				std::lock_guard<std::mutex> lock(queueMu);
				if (helperQueue.empty()) {
					break;
				}
				else {
					t = std::move(helperQueue.front());
					helperQueue.pop_front();
				}
			}
			t();
		}
	}

	void solveNQueensConcurrently(uint64_t n) {
		if (n == 1) {
			std::cout << "Q" << std::endl;
			return;
		}

		std::vector<std::string> currentBoard(n, std::string(n, '.'));
		//vector<vector<string>> answers;
		//with three uint64_ts I can find any solution where n < 32
		uint64_t colMask, deg45Mask, deg135Mask;
		colMask = deg45Mask = deg135Mask = 0;

		uint64_t cores = std::thread::hardware_concurrency() - 1;
		uint64_t cores_used = n < cores ? n : cores;

		std::vector<std::thread> threads;
		for (uint64_t col = 0; col < n; col++) {
			colMask ^= 1LL << col;
			deg45Mask ^= 1LL << (col);
			deg135Mask ^= 1LL << (n - 1 - col); //the row value is 0 so we remove it from the equation
			currentBoard[0][col] = 'Q';
			std::packaged_task<void(void)>
				aTask(std::bind(threadedHelper, currentBoard,
						colMask, deg45Mask, deg135Mask, n));
			currentBoard[0][col] = '.';
			colMask ^= 1LL << col;
			deg45Mask ^= 1LL << (col);
			deg135Mask ^= 1LL << (n - 1 - col); //the row value is 0 so we remove it from the equation
			helperQueue.push_back(std::move(aTask));
		}

		for (uint32_t i = 0; i < cores_used; i++) {
			threads.push_back(std::thread(thread_func));
			threads[i].join();
		}
	}


}
