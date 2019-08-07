#include "pch.h"
#include <vector>
#include <string>
#include "nQueens.h"

vector<vector<string>> NQueens::solveNQueens(int n) {
	if (n == 1) {
		vector<vector<string>> answer{ { "Q" } };
		return answer;
	}

	vector<int> queens;
	vector<string> currentBoard(n, string(n, '.'));
	vector<vector<string>> answers;
	//with three long long ints I can find any solution where n < 32
	long long int colMask, deg45Mask, deg135Mask;
	colMask = deg45Mask = deg135Mask = 0;

	helper(answers, currentBoard, queens, colMask, deg45Mask, deg135Mask, n, 0);
	return answers;
}

void NQueens::helper(vector<vector<string>> &answers,
	vector<string> &board,
	vector<int> &queens,
	long long int &colMask,
	long long int &deg45Mask,
	long long int &deg135Mask,
	int &n,
	int row) {
	if (row == n) {
		answers.push_back(board);
		return;
	}

	for (int col = 0; col < n; col++) {
		queens.push_back(col);

		if ((colMask ^ 1LL << col) > colMask
			&& (deg45Mask ^ 1LL << (row + col)) > deg45Mask
			&& (deg135Mask ^ 1LL << (n - 1 + row - col)) > deg135Mask
			) {
			colMask ^= 1LL << col;
			deg45Mask ^= 1LL << (row + col);
			deg135Mask ^= 1LL << (n - 1 + row - col);
			board[row][col] = 'Q';
			helper(answers, board, queens, colMask, deg45Mask, deg135Mask, n, row + 1);
			board[row][col] = '.';
			colMask ^= 1LL << col;
			deg45Mask ^= 1LL << (row + col);
			deg135Mask ^= 1LL << (n - 1 + row - col);
		}
		queens.pop_back();
	}
}