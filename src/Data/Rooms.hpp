#pragma once

#include <vector>
#include <string>

struct Room {
    std::string Id;
	std::string Name;
	std::string Dept;
	int         Capacity;
	bool        Bookable;

	std::string to_string();
};

class Rooms {
public:

Rooms();
Room& operator[](const int& a);

int size();
std::string to_string();

private:
std::vector<Room> data;
};