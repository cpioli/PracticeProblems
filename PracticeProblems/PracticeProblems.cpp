// PracticeProblems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "BinaryTree.h"

using namespace std;
//interpret .csv files
//void runCSVInterpreter(std::string &_filename);

//Tree functions
void runTreeTests(std::string &_filename);

//LinkedList functions
void runLinkedListTests(std::string &_filename);

//Calculator functions
void runSimpleCalculator(std::string &_filename);
int calculation(std::string &_line);

int main(int argc, char* argv[])
{
	std::string filename = "";
	int choice = 0;
	if (argc == 1) {
		std::cout << "Choose a function " << std::endl;
		std::cout << "1. Run Simple Calculations" << std::endl;
		std::cout << "2. Run LinkedList Tests" << std::endl;
		std::cout << "3. Interpret a CSV file" << std::endl;
		std::cout << "4. Trees" << std::endl;
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
		case 2:runLinkedListTests(filename); break;
		case 4:runTreeTests(filename); break;
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
		std::cout << s << " = " << calculation(s) << std::endl;
	}
}

int calculation(std::string &_line) {
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

//Singly LinkedList
void runLinkedListTests(std::string &_filename) {
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
