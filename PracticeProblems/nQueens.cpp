#include "pch.h"
#include <vector>
#include <string>
#include "nQueens.h"

uint64_t NQueens::solveNQueens(uint64_t n) {
	if (n == 1) {
		return 1;
	}

	//vector<uint64_t> queens;
	vector<string> currentBoard(n, string(n, '.'));
	//vector<vector<string>> answers;
	//with three uint64_ts I can find any solution where n < 32
	uint64_t colMask, deg45Mask, deg135Mask;
	colMask = deg45Mask = deg135Mask = 0;
	uint64_t answers = 0;
	helper(answers, currentBoard, /*queens,*/ colMask, deg45Mask, deg135Mask, n, 0);
	return answers;
}

void NQueens::helper(uint64_t &answers,
	vector<string> &board,
	//vector<uint64_t> &queens,
	uint64_t &colMask,
	uint64_t &deg45Mask,
	uint64_t &deg135Mask,
	uint64_t &n,
	uint64_t row) {
	if (row == n) {
		//answers.push_back(board);
		return;
	}

	for (uint64_t col = 0; col < n; col++) {
		//queens.push_back(col);

		if (!(colMask & (uint64_t)1 << col)
			&& !(deg45Mask & (uint64_t)1 << (row + col))
			&& !(deg135Mask & (uint64_t)1 << (n - 1 + row - col))
			) {
			colMask ^= 1LL << col;
			deg45Mask ^= 1LL << (row + col);
			deg135Mask ^= 1LL << (n - 1 + row - col);
			board[row][col] = 'Q';
			helper(answers, board, /*queens,*/ colMask, deg45Mask, deg135Mask, n, row + 1);
			board[row][col] = '.';
			colMask ^= 1LL << col;
			deg45Mask ^= 1LL << (row + col);
			deg135Mask ^= 1LL << (n - 1 + row - col);
		}
		//queens.pop_back();
	}
}