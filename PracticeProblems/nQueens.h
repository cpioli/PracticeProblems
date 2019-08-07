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
	vector<vector<string>> solveNQueens(int n);
private:
	void helper(vector<vector<string>> &answers,
		vector<string> &board,
		vector<int> &queens,
		long long int &colMask,
		long long int &deg45Mask,
		long long int &deg135Mask,
		int &n,
		int row);
};
