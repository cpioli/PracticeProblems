#pragma once

#include <string>
/*
The solution class will be an abstract class that provides functions to handle
Things
*/

class Solution {
private:
	std::string description;
	
public:
	virtual void Tests() = 0;
};