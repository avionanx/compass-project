#include "compass.h"
#include "data.h"
namespace compass {
	void readFile(std::string path, std::map<int, std::vector<float>> &userList, std::map<int, std::vector<float>>& filmList) {
		//io stuff
		std::ifstream file;
		std::string line;
		
		file.open(path, std::ios_base::in);

		//ignores first line of input file
		//ignore function skips set amount of chars, with max value, it ignores whole line.
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//
		//initializers for the main parser
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
		std::cout << "Number of numbers: " << i << std::endl;
		file.close();
	}

	float getNumberFromString(std::string str) {
		return std::stof(str); //float
	}

	int getRatingCount(int id) { return 0; }

	std::vector<int> getTopTenData(std::map<int, std::vector<float>>& dataList) {
		std::vector<int> dataAndRatings(20);

		
		std::vector<int> skipList(10);
		for (int x = 0; x < 10; x++) {
			int highestRatingID = 0;
			int highestDataID = 0;
			for (const auto kv : dataList) {
				int rating = kv.second.size() / 2;
				if (rating > highestRatingID){
					if (std::find(skipList.begin(), skipList.end(), kv.first) == skipList.end()) {
						highestRatingID = rating;
						highestDataID = kv.first;
					}
				}
			}
			std::cout << highestDataID << " " << highestRatingID << std::endl;
			skipList.push_back(highestDataID);
			dataAndRatings.push_back(highestDataID);
			dataAndRatings.push_back(highestRatingID);
		}
		return dataAndRatings;
	}

	double calculateSimilarity() {
		return 0.0f;//do this later
	}
}
