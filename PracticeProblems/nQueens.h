#pragma once
/*
My optimal solution for the N-Queens problem
I took the idea of creating bitmasks from another guy, but instead of using
vector<int> I used a single variable and bit-shifting to solve the problem.
*/

#include <vector>
#include <string>

using namespace std;
class NQueens {
public:
	uint64_t solveNQueens(uint64_t n);
private:
	void helper(uint64_t &answers,
		vector<string> &board,
		//vector<uint64_t> &queens,
		uint64_t &colMask,
		uint64_t &deg45Mask,
		uint64_t &deg135Mask,
		uint64_t &n,
		uint64_t row);
};
