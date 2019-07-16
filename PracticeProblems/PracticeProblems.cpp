// PracticeProblems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>


//interpret .csv files
//void runCSVInterpreter(std::ifstream &_file);

//Calculator functions
void runSimpleCalculator(std::string &_filename);
int calculation(std::string &_line);

int main(int argc, char* argv[])
{
	std::string filename = "";
	if (argc == 1) {
		int choice = 0;
		std::cout << "Choose a function " << std::endl;
		std::cout << "1. Run Simple Calculations" << std::endl;
		std::cout << "2. Run the CSV file interpreter" << std::endl;
		std::cin >> choice;
		switch (choice) {
			case 1:runSimpleCalculator(filename); break;
			//case 2:runCSVInterpreter(); break;
		}
		
	}
	else
	{

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
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
