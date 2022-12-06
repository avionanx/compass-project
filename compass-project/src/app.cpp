#include "app.h"
void App() {
	User users;
	compass::readFile("input/train.csv", users.userList);
	std::cout << users.userList.at(8927).size();
}

