#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
class Data {
private:
	
public:
	//maps are sorted w/ its key by default, could cause speed issues
	//could switch to map, sorting is cool though
	//for now its just 15% speedup w/ unordered, irrelevant.
	
	std::map<int, std::vector<float>> userList;
	//USERID (KEY)
	//MOVIEID
	//RATING

	//I keep thinking if I can get top 10 films with userList somehow
	//I don't want to create another big map just for this purpose, inefficient. 
	std::map<int, std::vector<float>> filmList;
	//MOVIEID (KEY)
	//USERID
	//RATING

	//
	std::map<int, std::vector<float>> testList;
	//KEY
	//USERID
	//MOVIEID
	//RATING (NULL at first)
	//read, then submit this file
};