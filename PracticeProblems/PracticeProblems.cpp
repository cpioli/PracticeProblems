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

	friend std::ostream & operator<<(std::ostream &out, const complexNumber &cn) {
		out << cn.regular << "+" << cn.complex << "i";
		return out;
	}
};

//interpret .csv files
//void runCSVInterpreter(std::string &_filename);

//Calculator functions
void runSimpleCalculator(std::string &_filename);
int calc(std::string &_line);

//Complex Calculator functions
void runComplexCalculator(std::string &_filename);
complexNumber complexCalc(std::string &_line);

//LinkedList functions
void runLinkedListTests(std::string &_filename);

//N-Queens function
void runNQueensTest();

//Tree functions
void runTreeTests(std::string &_filename);

int main(int argc, char* argv[])
{
	std::string filename = "";
	int choice = 0;
	if (argc == 1) {
		std::cout << "Choose a function " << std::endl;
		std::cout << "1. Run Simple Calculations" << std::endl;
		std::cout << "2. Run calculations on complex numbers" << std::endl;
		std::cout << "3. Run LinkedList Tests" << std::endl;
		std::cout << "4. Solve the N-Queens Problem" << std::endl;
		std::cout << "5. Trees!" << std::endl;
		//std::cout << "2. Run the CSV file interpreter" << std::endl;
		std::cin >> choice;
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
		default: std::cout << "Not implemented yet" << std::endl; break;
	}
	return 0;
}


void runSimpleCalculator(std::string &_filename) {
	std::ifstream calculations;
	if (_filename.size() == 0) {
		_filename = "simpleCalcProblems.txt";
	}
	try {
		calculations.open(_filename);
	}
	catch (const std::ifstream::failure) {
		std::cout << "Unable to open file" << std::endl;
		return;
	}

	if (!calculations) {
		std::cout << "Skipping!" << std::endl;
		return;
	}
	std::string s;
	while (std::getline(calculations, s)) {
		std::cout << s << " = " << calc(s) << std::endl;
	}
}

int calc(std::string &_line) {
	int total = 0;
	size_t intStart = 0, intEnd = 0;
	size_t nextSign = _line.find_first_of("+-");
	int i;
	total = std::stoi(_line.substr(intStart, nextSign));
	intStart = nextSign + 1;

	while (nextSign != std::string::npos) {
		intEnd = _line.find_first_of("+-", intStart);
		i = std::stoi(_line.substr(intStart, intEnd - intStart));
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

void runComplexCalculator(std::string &_filename) {
	std::ifstream calculations;
	if (_filename.size() == 0) {
		_filename = "complexCalcProblems.txt";
	}
	try {
		calculations.open(_filename);
	}
	catch (const std::ifstream::failure) {
		std::cout << "Unable to open file" << std::endl;
		return;
	}

	if (!calculations) {
		std::cout << "Skipping!" << std::endl;
		return;
	}
	std::string s;
	while (std::getline(calculations, s)) {
		std::cout << s << " = " << complexCalc(s) << std::endl;
	}
}

complexNumber complexCalc(std::string &_line) {
	_line.erase(remove_if(_line.begin(), _line.end(), isspace), _line.end());
	int32_t x = -1;
	cout << "x = " << x << endl;
	size_t complexCursor = _line.find_first_of("*");
	std::vector<std::string> ss = { _line.substr(0, complexCursor), _line.substr(complexCursor+1, _line.size() - complexCursor) };
	std::vector<complexNumber> nums;
	for (string s : ss) {
		//std::cout << s << std::endl;
		int plusLoc = s.find_first_of("+");
		cout << s[plusLoc + 1] << endl;
		bool neg = false;
		if (s[plusLoc + 1] == '-') {
			cout << "complex!" << endl;
			neg = true;
			plusLoc += 1;
		}
		int natural = std::stoi(s.substr(0, plusLoc));
		int complex = 0;
		int iLoc = s.find_first_of("i");
		complex = std::stoi(s.substr(plusLoc, iLoc - plusLoc));
		
		nums.push_back(complexNumber(natural, complex));
	}
	for (auto n : nums) cout << n << endl;
	//cout << nums[0] * nums[1] << endl;
	return nums[0] * nums[1];
}

//Singly LinkedList
void runLinkedListTests(std::string &_filename) {
	LinkedList<int> intList = LinkedList<int>();
	intList.push_back(111);
	intList.push_front(11);
	intList.push_front(1);
	std::cout << intList << endl;
	intList.resize(2);
	std::cout << "Resized!" << endl;
	std::cout << intList << endl;
	std::cout << intList.front() << endl;
	return;
}

//Binary Search Tree test
void runTreeTests(std::string &_filename) {
	BinarySearchTree<int> bst;
	bst.insert(500);
	bst.insert(422);
	bst.insert(300);
	bst.insert(1000);
	bst.insert(2);
	bst.insert(355);
	std::cout << "postorder traversal: "; bst.postorderPrint();
	std::cout << "preorder traversal:  "; bst.preorderPrint();
	std::cout << "inorder traveral:    "; bst.inorderPrint();
	bst.erase(300);
	std::cout << "Erased the number 300!" << std::endl;
	std::cout << "postorder traversal: "; bst.postorderPrint();
	std::cout << "preorder traversal:  "; bst.preorderPrint();
	std::cout << "inorder traveral:    "; bst.inorderPrint();
}

void runNQueensTest() {
	NQueens solver;
	vector<vector<string>> queens = solver.solveNQueens(5);
	for (vector<string> solution : queens) {
		for (string row : solution) {
			std::cout << row << std::endl;
		}
		std::cout << std::endl;
	}
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
