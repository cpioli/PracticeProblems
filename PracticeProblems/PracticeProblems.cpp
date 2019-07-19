// PracticeProblems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"

//interpret .csv files
//void runCSVInterpreter(std::string &_filename);

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
	intList.push_front(1);
	std::cout << intList << std::endl;
	intList.push_front(66);
	std::cout << intList << std::endl;
	intList.push_back(102);
	std::cout << intList << std::endl;
	intList.insert_after(102, 55);
	std::cout << intList << std::endl;
	intList.insert_before(66, 12);
	std::cout << intList << std::endl;
	intList.insert_after(55, 22);

	auto iter = intList.begin();
	while (iter != intList.end()) {
		std::cout << *iter->m_value << " " << std::endl;
		iter++;
	}

	std::cout << intList << std::endl;
	intList.erase_after(66);
	std::cout << intList << std::endl;
	intList.erase(66);
	std::cout << intList << std::endl;
	intList.reverse();
	std::cout << intList << std::endl;
	intList.pop_front();
	std::cout << intList << std::endl;
	intList.erase(55);
	std::cout << intList << std::endl;
	intList.reverse();
	std::cout << intList << std::endl;
	LinkedList<int> intList2 = LinkedList<int>();
	intList2.push_front(5);
	intList2.push_back(205);
	intList2.push_back(455);
	intList2.push_back(600);
	intList2.push_back(50000);
	intList += intList2;
	std::cout << intList << std::endl;
	intList.push_back(200);
	intList.push_front(0);
	std::cout << intList << std::endl;
	intList = intList2;
	std::cout << intList << std::endl;
	return;
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
