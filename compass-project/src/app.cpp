#include "app.h"
void App() {
	User users; //the amazing user class which holds just a single variable, a big one at that.
	compass::readFile("input/train.csv", users.userList); //reads input file and writes to userList of users
	int highestRatingID = 0;
	int highestUserID = 0;
	for (const auto& kv : users.userList) {
		bool take = true;
		int rating = 0;
		for (auto i : kv.second) {
			take = !take;
			if (take == false) {
				continue;
			}
			
			rating = rating + i;
		}
		if (rating > highestRatingID) {
			highestRatingID = rating;
			highestUserID = kv.first;
		}
	}
	std::cout << "Highest rating is with User ID: " << highestUserID << " with Rating :" << highestRatingID << std::endl;

}

