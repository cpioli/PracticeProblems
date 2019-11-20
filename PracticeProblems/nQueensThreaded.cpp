#include "pch.h"
#include "nQueensThreaded.h"

namespace cpioli {
	std::mutex queueMu;
	std::mutex answerMu;

	//std::vector<std::vector<std::string>> answers;
	int nextTask = 0;
	int answers = 0;

	void solveNQueensConcurrently(uint64_t n) {
		if (n == 1) {
			std::cout << "Q" << std::endl;
			return;
		}
		answers = 0;
		std::vector<std::string> currentBoard(n, std::string(n, '.'));

		uint64_t cores = std::thread::hardware_concurrency() - 1;
		std::cout << "Cores in cpu: " << cores << std::endl;
		uint64_t cores_used = std::min(n, cores);

		std::vector<std::thread> threads;

		for (uint32_t i = 0; i < cores_used; i++) {
			//auto makeThreadStart = std::chrono::high_resolution_clock::now();
			threads.push_back(std::thread(cpioli::threadRequestTask, currentBoard, std::ref(n)));
			//auto makeThreadEnd = std::chrono::high_resolution_clock::now();
			//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(makeThreadEnd - makeThreadStart).count();
			//std::cout << "Made thread " << threads[i].get_id() << " in " << duration << " microseconds" << std::endl;
		}
		for (uint32_t i = 0; i < cores_used; i++) {
			threads[i].join();
		}
		std::cout << "Solutions: " << answers << std::endl; // .size() << std::endl;
	}

	void threadRequestTask(std::vector<std::string> board, uint64_t& n) {
		int threadsTaskColumn = 0;
		uint64_t colMask = 0, deg45Mask=0, deg135Mask=0;

		while (true) {
			if (nextTask == n) break;
			{
				std::lock_guard<std::mutex> lock(queueMu);
				threadsTaskColumn = nextTask;
				nextTask++;
			} 
			colMask = 1LL << threadsTaskColumn;
			deg45Mask = 1LL << threadsTaskColumn;
			deg135Mask = 1LL << (n - 1 - threadsTaskColumn);
			board[0][threadsTaskColumn] = 'Q';
			beginTask(board, colMask, deg45Mask, deg135Mask, n, 1);
			board[0][threadsTaskColumn] = '.';
		}
	}

	//I THINK THE ISSUE IS PASSING A VARIABLE BY REFERENCE INTO A BOUND FUNCTION
//INSTEAD I SHOULD PASS-BY-VALUE INTO threadedHelper, AND THEN threadedHelper
//PASSES THE VALUES BY-REFERENCE INTO THE RECURSIVE FUNCTION helper!

	void beginTask(std::vector<std::string> &board,
		uint64_t &colMask,
		uint64_t &deg45Mask,
		uint64_t &deg135Mask,
		uint64_t &n,
		uint64_t row) {

		if (row == n) {
			std::lock_guard<std::mutex> lock(answerMu);
			answers++;
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
				beginTask(board, colMask, deg45Mask, deg135Mask, n, row + 1);
				board[row][col] = '.';
				colMask ^= 1LL << col;
				deg45Mask ^= 1LL << (row + col);
				deg135Mask ^= 1LL << (n - 1 + row - col);
			}
		}
	}




	

}
