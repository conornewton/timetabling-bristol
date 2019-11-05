#pragma once

#include <vector>
#include <string>

class Teacher {
    std::string ID;
	bool pathway_one = false;          //which day is the staff members research day, (If it is -1 then they dont have a research day)
	std::vector<int> activities;       //Activities the staff member is teaching
	std::vector<int> bad_timeslots;    //timeslots the staff member is not free during
};

class Teachers {
public:

Teachers();
Teacher& operator[](const int& a);

private:
std::vector<Teacher> data;

};