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
#include <cmath>
#include "data.h"
#include <tuple>
typedef std::map<int, std::vector<float>>& compassData;
namespace compass {

	//gets file and writes data to user list
	void readFile(std::string path, std::map<int, std::vector<float>>& userList, std::map<int, std::vector<float>>& filmList);
	//runs stof on words, readfile helper function
	float getNumberFromString(std::string s);
	//gets top 10 users/films via algorithm
	std::vector<int> getTopTenData(std::map<int, std::vector<float>>& dataList);
	//reads test file
	void readTestFile(std::string path, std::map<int, std::vector<float>>& testList);
	//calculates cosine similarity
	std::pair<float,int> calculateCosineSimilarity(std::vector<float>& A, std::vector<float>& B);
	float cosineFormula(const std::vector<float>& A, const std::vector<float>& B);
	//prints
	void printGuess(std::map<int, std::vector<float>>& dataList);
	//writes to test file with result from printGuess
	void guessRating(std::map<int, std::vector<float>>& userList, std::map<int, std::vector<float>>& testList);
	//checks if the movie is watched
	bool hasWatchedMovie(std::vector<float >& dataList, float movieID);
	float roundToHalf(float i);
}