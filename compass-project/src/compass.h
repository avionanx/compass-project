#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <sstream>
#include <map>
#include <vector>
namespace compass {
	void readFile(std::string path, std::map<int, std::vector<float>> &userList);
	float getNumberFromString(std::string s);
	int getRatingCount(int id);
}