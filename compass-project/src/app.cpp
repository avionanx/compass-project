#include "app.h"
void App() {
	Data data; //the amazing data class
	//std::cout << data.testList.at(1).size();

	compass::readFile("input/mytrain.txt", data.userList, data.filmList); //reads input file and writes to userList of users
	compass::readTestFile("input/mytest.txt", data.testList);

	compass::guessRating(data.userList,data.testList);


	
	compass::printGuess(data.testList);
	//std::vector<int> userTopRatings = compass::getTopTenData(data.userList);
	//std::vector<int> filmTopRatings = compass::getTopTenData(data.filmList);

	//std::cout<< "cosine thing is: " << compass::calculateCosineSimilarity(data.userList.at(2199), data.userList.at(22178)) << std::endl;

}
