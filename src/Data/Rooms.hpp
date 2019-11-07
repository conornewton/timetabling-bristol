#pragma once

#include <vector>
#include <string>
#include <unordered_map>

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
int id_to_index(const std::string& id);

Room* begin();
Room* end();

private:
std::vector<Room> data;
std::unordered_map<std::string, int> id_to_index_map;
};