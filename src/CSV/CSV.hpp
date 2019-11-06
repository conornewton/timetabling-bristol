#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, const char& delim);

class CSV
{
public:
	CSV(std::string FILEPATH);
	~CSV();

	bool next_line();
	std::vector<std::string> get_values();

private:
	std::fstream fin;
	int index = 0;

	std::vector<std::string> lines;
};
