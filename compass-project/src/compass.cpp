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
		std::cout << "Reading training file is completed \n";
		file.close();
	}

	float getNumberFromString(std::string str) {
		return std::stof(str); //float
	}

	std::vector<int> getTopTenData(std::map<int, std::vector<float>>& dataList) {
		std::vector<int> dataAndRatings(20);


		std::vector<int> skipList(10);
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
		std::cout << "Number of numbers: " << i << std::endl;
		file.close();
	}

	float calculateCosineSimilarity(std::vector<float>& A, std::vector<float>& B) {
		int sameMoviesFound = 0;
		std::vector<float> movieRatingA;
		std::vector<float> movieRatingB;
		if (A.size() < B.size()) {
			for (int x = 0; x < A.size(); x += 2) {
				for (int y = x; y < B.size(); y += 2) {
					if (A[x] == B[y]) {
						sameMoviesFound++;
						movieRatingA.push_back(A[x + 1]);
						movieRatingB.push_back(B[y + 1]);

						//std::cout << A[x] << " " << A[x + 1] << " " << B[y + 1] << std::endl;
					}

				}
			}
		}
		else {
			for (int x = 0; x < B.size(); x += 2) {
				for (int y = x; y < A.size(); y += 2) {
					if (A[y] == B[x]) {
						sameMoviesFound++;
						movieRatingA.push_back(A[y + 1]);
						movieRatingB.push_back(B[x + 1]);

						//std::cout << A[y] << " " << A[y + 1] << " " << B[x + 1] << std::endl;
					}
				}
			}
		}

		if (movieRatingA.empty() || movieRatingA.size() < 1) {
			return -1;
		}
		return cosineFormula(movieRatingA, movieRatingB);
	}

	float cosineFormula(const std::vector<float>& A, const std::vector<float>& B) {
		float numerator = 0.0f;
		float denominator = 1.0f; //dont want 0.0/0.0 really
		for (int i = 0; i < A.size(); i++) {
			numerator += (double)A[i] * B[i];
		}
		//std::cout << "numumerator is" << numerator << std::endl;
		float l = 0.0f;
		float r = 0.0f;
		for (const auto& n : A) {
			l += pow(n, 2);
		}
		l = sqrt(l);
		for (const auto& n : A) {
			r += pow(n, 2);
		}
		r = sqrt(r);
		denominator = l * r;
		return numerator / denominator;
	}

	void printGuess(std::map<int, std::vector<float>>& dataList) {
		int index = 0;
		for (const auto& c : dataList) {
			std::cout << c.first << " " << c.second[0] << " " << c.second[1] << " " << c.second[2] << std::endl;
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
}
