// PracticeProblems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LinkedList.h"
#include "BinaryTree.h"
#include "nQueens.h"
#include "nQueensThreaded.h"

using namespace std;

struct complexNumber {
public:
	int32_t regular;
	int32_t complex;

	complexNumber(int32_t _reg, int32_t _com) : regular(_reg), complex(_com) {};

	complexNumber operator*(complexNumber &right) {
		int newRegular = regular * right.regular - complex * right.complex;

		complex = regular * right.complex + complex * right.regular;
		regular = newRegular;
		return *this;
	}

	friend ostream & operator<<(ostream &out, const complexNumber &cn) {
		out << cn.regular << "+" << cn.complex << "i";
		return out;
	}
};

//interpret .csv files
//void runCSVInterpreter(string &_filename);

//Calculator functions
void runSimpleCalculator(string &_filename);
int calc(string &_line);

//Complex Calculator functions
void runComplexCalculator(string &_filename);
complexNumber complexCalc(string &_line);

//LinkedList functions
void runLinkedListTests(string &_filename);

//N-Queens function
void runNQueensTest();
void runNQueensComparison();
void runConcurrentNQueensTest();

//Tree functions
void runTreeTests(string &_filename);

int main(int argc, char* argv[])
{
	string filename = "";
	int choice = 0;
	if (argc == 1) {
		cout << "Choose a function " << endl;
		cout << "1. Run Simple Calculations" << endl;
		cout << "2. Run calculations on complex numbers" << endl;
		cout << "3. Run LinkedList Tests" << endl;
		cout << "4. Solve the N-Queens Problem" << endl;
		cout << "5. Trees!" << endl;
		cout << "6. Solve the N-Queens Problem concurrently!" << endl;
		cout << "7. Compare Concurrent and Single Threaded N-Queens solutions!" << endl;
		//cout << "2. Run the CSV file interpreter" << endl;
		cin >> choice;
	}
	else
	{
		choice = atoi(argv[1]);
		filename = argv[2];
	}
	switch (choice) {
		case 1:runSimpleCalculator(filename); break;
		case 2:runComplexCalculator(filename); break;
		case 3:runLinkedListTests(filename); break;
		case 4:runNQueensTest(); break;
		case 5:runTreeTests(filename); break;
		case 6:runConcurrentNQueensTest(); break;
		case 7:runNQueensComparison(); break;
		default: cout << "Not implemented yet" << endl; break;
	}
	return 0;
}


void runSimpleCalculator(string &_filename) {
	ifstream calculations;
	if (_filename.size() == 0) {
		_filename = "simpleCalcProblems.txt";
	}
	try {
		calculations.open(_filename);
	}
	catch (const ifstream::failure) {
		cout << "Unable to open file" << endl;
		return;
	}

	if (!calculations) {
		cout << "Skipping!" << endl;
		return;
	}
	string s;
	while (getline(calculations, s)) {
		cout << s << " = " << calc(s) << endl;
	}
}

int calc(string &_line) {
	int total = 0;
	size_t intStart = 0, intEnd = 0;
	size_t nextSign = _line.find_first_of("+-");
	int i;
	total = stoi(_line.substr(intStart, nextSign));
	intStart = nextSign + 1;

	while (nextSign != string::npos) {
		intEnd = _line.find_first_of("+-", intStart);
		i = stoi(_line.substr(intStart, intEnd - intStart));
		if (_line[nextSign] == '+') {
			total += i;
		}
		else {
			total -= i;
		}
		nextSign = intEnd;
		intStart = nextSign + 1;
	}
	return total;
}

void runComplexCalculator(string &_filename) {
	ifstream calculations;
	if (_filename.size() == 0) {
		_filename = "complexCalcProblems.txt";
	}
	try {
		calculations.open(_filename);
	}
	catch (const ifstream::failure) {
		cout << "Unable to open file" << endl;
		return;
	}

	if (!calculations) {
		cout << "Skipping!" << endl;
		return;
	}
	string s;
	while (getline(calculations, s)) {
		cout << s << " = " << complexCalc(s) << endl;
	}
}

complexNumber complexCalc(string &_line) {
	_line.erase(remove_if(_line.begin(), _line.end(), isspace), _line.end());
	int32_t x = -1;
	cout << "x = " << x << endl;
	size_t complexCursor = _line.find_first_of("*");
	vector<string> ss = { _line.substr(0, complexCursor), _line.substr(complexCursor+1, _line.size() - complexCursor) };
	vector<complexNumber> nums;
	for (string s : ss) {
		//cout << s << endl;
		int plusLoc = s.find_first_of("+");
		cout << s[plusLoc + 1] << endl;
		bool neg = false;
		if (s[plusLoc + 1] == '-') {
			cout << "complex!" << endl;
			neg = true;
			plusLoc += 1;
		}
		int natural = stoi(s.substr(0, plusLoc));
		int complex = 0;
		int iLoc = s.find_first_of("i");
		complex = stoi(s.substr(plusLoc, iLoc - plusLoc));
		
		nums.push_back(complexNumber(natural, complex));
	}
	for (auto n : nums) cout << n << endl;
	//cout << nums[0] * nums[1] << endl;
	return nums[0] * nums[1];
}

//Singly LinkedList
void runLinkedListTests(string &_filename) {
	LinkedList<int> intList = LinkedList<int>();
	intList.push_back(111);
	intList.push_front(11);
	intList.push_front(1);
	cout << intList << endl;
	intList.resize(2);
	cout << "Resized!" << endl;
	cout << intList << endl;
	cout << intList.front() << endl;
	return;
}

//Binary Search Tree test
void runTreeTests(string &_filename) {
	BinarySearchTree<int> bst;
	bst.insert(500);
	bst.insert(422);
	bst.insert(300);
	bst.insert(1000);
	bst.insert(2);
	bst.insert(355);
	cout << "postorder traversal: "; bst.postorderPrint();
	cout << "preorder traversal:  "; bst.preorderPrint();
	cout << "inorder traveral:    "; bst.inorderPrint();
	bst.erase(300);
	cout << "Erased the number 300!" << endl;
	cout << "postorder traversal: "; bst.postorderPrint();
	cout << "preorder traversal:  "; bst.preorderPrint();
	cout << "inorder traveral:    "; bst.inorderPrint();
}

void runNQueensTest() {
	NQueens solver;
	uint64_t count = solver.solveNQueens(8);
	cout << count << endl;
}

void runConcurrentNQueensTest() {

	auto nQueenStart_mt = std::chrono::high_resolution_clock::now();
	cpioli::solveNQueensConcurrently(13);
	auto nQueenEnd_mt = std::chrono::high_resolution_clock::now();
	auto duration_mt = std::chrono::duration_cast<std::chrono::microseconds>(nQueenEnd_mt - nQueenStart_mt).count();
	cout << "Multi-threaded run : " << duration_mt << endl;

}

void runNQueensComparison() {
	NQueens solver;
	auto nQueenStart = std::chrono::high_resolution_clock::now();
	uint64_t count = solver.solveNQueens(11);
	auto nQueenEnd = std::chrono::high_resolution_clock::now();

	auto nQueenStart_mt = std::chrono::high_resolution_clock::now();
	cpioli::solveNQueensConcurrently(11);
	auto nQueenEnd_mt = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(nQueenEnd - nQueenStart).count();
	auto duration_mt = std::chrono::duration_cast<std::chrono::microseconds>(nQueenEnd_mt - nQueenStart_mt).count();

	cout << "Single threaded run: " << duration << endl;
	cout << "Multi-threaded run : " << duration_mt << endl;
	double faster = (float)(duration - duration_mt) / (float)duration * 100.0f;
	cout << "MT run is : " << faster << "% faster than ST run!" << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
