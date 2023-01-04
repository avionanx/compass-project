#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
class Data {
private:
	
public:
	//maps are sorted w/ its key by default, could cause speed issues
	//can switch to std::array for speed boost
	
	std::map<int, std::vector<float>> userList;
	//USERID (KEY)
	//MOVIEID
	//RATING

	//create another vector for top 10 films
	std::map<int, std::vector<float>> filmList;
	//MOVIEID (KEY)
	//USERID
	//RATING

	//missing data
	std::map<int, std::vector<float>> testList;
	//KEY
	//USERID
	//MOVIEID
	//RATING (NULL at first)
};