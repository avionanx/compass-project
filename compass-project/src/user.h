#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
class User {
private:
	
public:
	//maps are sorted w/ its key by default, could cause speed issues
	//could switch to unordered_map, sorting is cool though
	std::map<int, std::vector<float>> userList;
	//for now its just 15% speedup w/ unordered, irrelevant.
};