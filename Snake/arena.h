#pragma once
#include <unordered_map>
#include <string>
class arena
{
public:
	arena();
	std::string name;
	std::unordered_map<int, std::string> obstacles;
	int width;
	int height;
	
};

