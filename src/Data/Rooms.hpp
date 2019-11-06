#pragma once

#include <vector>
#include <string>

class Room {
    std::string Id;
	std::string Name;
	std::string Dept;
	int         Capacity;
	bool        Bookable;
};

class Rooms {
public:

Rooms();

Room& operator[](const int& a);
int size();

private:
std::vector<Room> data;
};