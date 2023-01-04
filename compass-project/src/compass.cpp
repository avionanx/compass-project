#include "compass.h"
#include "data.h"
namespace compass {
	void readFile(std::string path, std::map<int, std::vector<float>>& userList, std::map<int, std::vector<float>>& filmList) {
		//io stuff
		std::ifstream file;
		std::string line;

		file.open(path, std::ios_base::in);
		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file, please check your path. ");
		}
		//ignores first line of input file
		//ignore function skips set amount of chars, with max value, it ignores whole line.
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//
		//initializers for the main function
		int i = 0;
		int index = 0;
		float movieID, rating = 0.0f;
		//
		while (std::getline(file, line, '\n')) {		//seperate file line by line
			std::stringstream ss(line);
			while (getline(ss, line, ',')) {			//now seperate line by commas, leaving string "integers"
				//fake multidimensional (2D) vector implementation 
				//somehow this reduced memory usage by around 80% and runtime by 25%, cant complain
				if (i % 3 == 0) {
					index = getNumberFromString(line);	//first column, userID or index, etc.

				}
				else if (i % 3 == 1) {
					movieID = getNumberFromString(line);//second column, movieID
				}
				else {
					rating = getNumberFromString(line); //third column, movie ratings
				}
				if (i < 2) //cant push to userList yet since theres still blank data
				{
					i++;
					continue;
				}
				i++;
				if (i % 3 == 0) {
					userList[index].emplace_back(movieID);
					userList[index].emplace_back(rating);
					filmList[movieID].emplace_back(index);
					filmList[movieID].emplace_back(rating);
				}
			}
		}
		file.close();
	}

	float getNumberFromString(std::string str) {
		return std::stof(str); //float
	}

	std::vector<int> getTopTenData(std::map<int, std::vector<float>>& dataList) {
		std::vector<int> dataAndRatings;//init


		std::vector<int> skipList(10);//skips if its already in data list
		for (int x = 0; x < 10; x++) {
			int highestRatingID = 0;
			int highestDataID = 0;
			for (const auto kv : dataList) {
				int rating = kv.second.size() / 2;
				if (rating > highestRatingID) {
					if (std::find(skipList.begin(), skipList.end(), kv.first) == skipList.end()) {
						highestRatingID = rating;
						highestDataID = kv.first;
					}
				}
			}
			//std::cout << highestDataID << " " << highestRatingID << std::endl;
			//std::cout << highestDataID << " " << highestRatingID << std::endl;
			skipList.push_back(highestDataID);
			dataAndRatings.push_back(highestDataID);
			dataAndRatings.push_back(highestRatingID);
		}
		return dataAndRatings;
	}
	
	void readTestFile(std::string path, std::map<int, std::vector<float>>& testList) {
		//io stuff
		std::ifstream file;
		std::string line;

		file.open(path, std::ios_base::in);

		//ignores first line of input file
		//ignore function skips set amount of chars, with max value, it ignores whole line.
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//
		//initializers for the main function
		int i = 0; //for fake 2d vectors
		int index = 0;//key for map
		float userID, movieID = 0.0f; //self explanatory
		//
		while (std::getline(file, line, '\n')) {		//seperate file line by line
			std::stringstream ss(line);
			while (getline(ss, line, ',')) {			//now seperate line by commas, leaving string "integers"
				//fake multidimensional (2D) vector implementation 
				//somehow this reduced memory usage by around 80% and runtime by 25%, cant complain
				if (i % 3 == 0) {
					index = getNumberFromString(line);	//first column, KEY.
				}
				else if (i % 3 == 1) {
					userID = getNumberFromString(line);	//first column, USERID.
				}
				else if (i % 3 == 2) {
					movieID = getNumberFromString(line);//second column, MOVIEID.
				}

				if (i < 2) //cant push to userList yet since theres still blank data
				{
					i++;
					continue;
				}
				i++;
				if (i % 3 == 0) {
					testList[index].emplace_back(userID);
					testList[index].emplace_back(movieID);
					testList[index].emplace_back(NULL);//append 0 to the end to be calculated by cosine algorithm thing later 
					//std::cout <<  index<<" " << testList[index][i % 3] <<" " << testList[index][(i + 1) % 3] << " " << testList[index][(i + 2) % 3] << std::endl;
				}
			}
		}
		file.close();
	}

	std::pair<float,int> calculateCosineSimilarity(std::vector<float>& A, std::vector<float>& B) {
		int sameMoviesFound = 0;
		std::vector<float> movieRatingA;
		std::vector<float> movieRatingB;

		if (A.size() < B.size()) {
			for (int x = 0; x < A.size(); x += 2) {
				for (int y = 0; y < B.size(); y += 2) {
					if (A[x] == B[y]) {
						sameMoviesFound++;
						movieRatingA.push_back(A[x + 1]);
						movieRatingB.push_back(B[y + 1]);
					}

				}
			}
		}
		else {
			for (int x = 0; x < B.size(); x += 2) {
				for (int y = 0; y < A.size(); y += 2) {
					if (A[y] == B[x]) {
						sameMoviesFound++;
						movieRatingA.push_back(A[y + 1]);
						movieRatingB.push_back(B[x + 1]);

						//std::cout << A[y] << " " << A[y + 1] << " " << B[x + 1] << std::endl;
					}
				}
			}
		}
		if (movieRatingA.empty() || movieRatingA.size() <= 1) {
			return std::make_pair(0, 0);
		}
		
		return std::make_pair(cosineFormula(movieRatingA, movieRatingB),sameMoviesFound);
	}

	float cosineFormula(const std::vector<float>& A, const std::vector<float>& B) {
		float numerator = 0.0f;
		float denominator = 0.0f; //dont want 0.0/0.0 really
		for (int i = 0; i < A.size(); i++) {
			numerator += (double)A[i] * B[i];
		}
		float l = 0.0f;
		float r = 0.0f;
		for (const auto& n : A) {
			l += std::pow(n, 2);
		}
		l = std::sqrt(l);
		for (const auto& n : B) {
			r += std::pow(n, 2);
		}
		r = std::sqrt(r);
		
		denominator = l * r;
		if (denominator == 0) {
			return 0;
		}
		return numerator / denominator;
	}

	void printGuess(std::map<int, std::vector<float>>& dataList) {
		int index = 0;
		for (const auto& c : dataList) {
			//std::cout << c.first << " " << c.second[0] << " " << c.second[1] << " " << c.second[2] << std::endl;
			std::cout << c.first << " " << c.second[2] << std::endl;
		}
	}

	bool hasWatchedMovie(std::vector<float >& dataList, float movieID) {
		bool hasWatchedMovie = false;
		for (int i = 0; i < dataList.size(); i += 2) {
			if (dataList[i] == movieID)
				hasWatchedMovie = true;
		}
		return hasWatchedMovie;
	}

	void guessRating(std::map<int, std::vector<float>>& userList, std::map<int, std::vector<float>>& testList) {
		for (const auto& q : testList) {

			std::vector <float> numerator;
			std::vector <float> denominator;
			int i = q.first;
			float missingMovieID = q.second[1];
			float userIDA = q.second[0];

			double bestSimilarity = 0.0f;
			int bestMatch = 0;

			for (const auto& p : userList) {
				auto b = p.first;
				if (!compass::hasWatchedMovie(userList.at(b), missingMovieID)) {
					continue; //skip if chosen user has not watched the missing movie
				}
				else if (userIDA == b) {
					continue; //skip if chosen user is same as test user
				}
				else if (std::find(userList.at(b).begin(), userList.at(b).end(), missingMovieID) == userList.at(b).end()) {
					continue; //skip if its at end
				}
				//return pair since I need to return 2 values
				std::pair<float,int> resultPair = compass::calculateCosineSimilarity(userList.at(userIDA), userList.at(b));
				int IndexOfMovieAtB = 0;
				IndexOfMovieAtB = std::find(userList.at(b).begin(), userList.at(b).end(), missingMovieID) - userList.at(b).begin();
				while (IndexOfMovieAtB % 2 != 0 && userList.at(b)[IndexOfMovieAtB] <= 5) {
					//start at next step instead of index begin
					IndexOfMovieAtB = std::find(userList.at(b).begin() + IndexOfMovieAtB + 1, userList.at(b).end(), missingMovieID) - userList.at(b).begin();
				}
				numerator.push_back(userList.at(b)[IndexOfMovieAtB + 1] * resultPair.first* resultPair.second);
				denominator.push_back(resultPair.first* resultPair.second);
			}
			float n_sum = 0;
			float d_sum = 0;
			for (float i : numerator) {
				n_sum += i;
			}
			for (float i : denominator) {
				d_sum += i;
			}
			float ratingGuess = n_sum / d_sum;
			testList.at(i)[2] = ratingGuess;
			
		}
	}
	//round to half since ratings like 3.8 cannot exist, didnt help with RMSE though.
	float roundToHalf(float i) {
		return(floor((i * 2) + 0.5) / 2);
	}
}
