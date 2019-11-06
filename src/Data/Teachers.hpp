#pragma once

#include <vector>
#include <string>

struct Teacher {
    std::string ID;
	bool pathway_one = false;          //does the teacher require a resarch day, (If it is false then they dont have a research day)
	std::vector<int> activities;       //Activities the teacher member is teaching
	std::vector<int> bad_timeslots;    //timeslots the teacher member is not free during
};

class Teachers {
public:

Teachers();
Teacher& operator[](const int& a);
int size();

private:
std::vector<Teacher> data;

};