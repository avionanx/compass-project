#include "compass.h"
#include "user.h"
namespace compass {
	void readFile(std::string path, std::map<int, std::vector<std::vector<float>>> &userList) {
		std::ifstream file;
		std::string line;
		int i = 0;
		file.open(path, std::ios_base::in);
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		int index = 0;
		float movieID = 0.0f;
		float rating = 0.0f;
		while (std::getline(file, line, '\n')) {
			std::stringstream ss(line);
			while (getline(ss, line, ',')) {
				if (i % 3 == 0) {
					index = getNumberFromString(line);
				}
				else if (i % 3 == 1) {
					movieID = getNumberFromString(line);
				}
				else {
					rating = getNumberFromString(line);
				}
				if (i < 2)
				{
					i++;
					continue;
				}
				i++;
				if (i % 3 == 0) {
					userList[index].push_back({ movieID,rating });
				}
			}
		}
		std::cout << "Number of numbers: " << i << std::endl;
		file.close();
	}

	float getNumberFromString(std::string str) {
		return std::stof(str);
	}
}
