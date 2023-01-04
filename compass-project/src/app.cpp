#include "app.h"
void App() {
	Data data; //initialize data containers
	//read datas
	compass::readFile("input/train.csv", data.userList, data.filmList); //reads input file and writes to userList of users
	compass::readTestFile("input/test.csv", data.testList); //reads test file and prepares empty datas
	
	//find users that rated most movies and movies that have most ratings
	std::vector<int> userTopRatings = compass::getTopTenData(data.userList);
	for (int i = 0; i < userTopRatings.size(); i += 2) {
		std::cout << userTopRatings[i] << " " << userTopRatings[i + 1] << std::endl;
	}
	std::cout << "\n\n";
	std::vector<int> filmTopRatings = compass::getTopTenData(data.filmList);
	for (int i = 0; i < filmTopRatings.size(); i += 2) {
		std::cout << filmTopRatings[i] << " " << filmTopRatings[i + 1] << std::endl;
	}
	//
	std::cout << "\n\n";
	//guess ratings
	compass::guessRating(data.userList,data.testList);
	compass::printGuess(data.testList);


}
