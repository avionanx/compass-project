#include "app.h"
void App() {
	Data data; //the amazing data class
	//std::cout << data.testList.at(1).size();

	compass::readFile("input/train.csv", data.userList, data.filmList); //reads input file and writes to userList of users
	compass::readTestFile("input/test.csv", data.testList);
	for (const auto& q : data.testList) {

		int i = q.first;
		float missingMovieID = q.second[1];
		float userIDA = q.second[0];

		double bestSimilarity = 0.0f;
		int bestMatch = 0;

		for (const auto& p : data.userList) {
			auto b = p.first;
			if (!compass::hasWatchedMovie(data.userList.at(b), missingMovieID)) {
				continue;
			}
			else if (userIDA == b) {
				continue;
			}
			else if (data.userList.find(b) == data.userList.end() || data.userList.find(userIDA) == data.userList.end()) {
				continue;
			}
			else if (std::find(data.userList.at(b).begin(), data.userList.at(b).end(), missingMovieID) == data.userList.at(b).end()) {
				continue;
			}
			double similarity = compass::calculateCosineSimilarity(data.userList.at(userIDA), data.userList.at(b));
			if (abs(similarity - 1.0f) < abs(bestSimilarity - 1.0f)) {

				bestSimilarity = similarity;
				bestMatch = b;
			}
		}
		//std::cout << a << " best matches " << bestMatch << " with cosine: " << bestSimilarity << std::endl;
		int IndexOfMovieAtB = std::find(data.userList.at(bestMatch).begin(), data.userList.at(bestMatch).end(), missingMovieID) - data.userList.at(bestMatch).begin();
		float ratingGuess = data.userList.at(bestMatch)[IndexOfMovieAtB + 1];
		data.testList.at(i)[2] = ratingGuess;
		std::cout << i << std::endl;
		std::cout << "first user is: " << userIDA << " second user is: " << bestMatch << " guessing rating : " << ratingGuess << " similarity is:" << bestSimilarity << std::endl;
		//std::cin.get();
	}

	compass::printGuess(data.testList);
	//std::vector<int> userTopRatings = compass::getTopTenData(data.userList);
	//std::vector<int> filmTopRatings = compass::getTopTenData(data.filmList);

	//std::cout<< "cosine thing is: " << compass::calculateCosineSimilarity(data.userList.at(2199), data.userList.at(22178)) << std::endl;

}
