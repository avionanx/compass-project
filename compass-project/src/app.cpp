#include "app.h"
void App() {
	Data data; //the amazing data class
	compass::readFile("input/train.csv", data.userList, data.filmList); //reads input file and writes to userList of users
	std::vector<int> userTopRatings = compass::getTopTenData(data.userList);
	//std::vector<int> filmTopRatings = compass::getTopTenData(data.filmList);

	//std::cout << "Highest rating is with User ID: " << highestUserID << " with Rating :" << highestRatingID << std::endl;

}

