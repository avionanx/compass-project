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
	//gets file and writes data to user list
	void readFile(std::string path, std::map<int, std::vector<float>> &userList, std::map<int, std::vector<float>>& filmList);
	//runs stof on words, readfile helper function
	float getNumberFromString(std::string s);
	//useless function, to be deleted
	int getRatingCount(int id);
	//gets top 10 users/films via algorithm
	std::vector<int> getTopTenData(std::map<int, std::vector<float>>& dataList);

	double calculateSimilarity();
}