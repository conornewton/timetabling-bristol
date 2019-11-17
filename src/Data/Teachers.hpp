#pragma once

#include <vector>
#include <string>
#include <unordered_map>

struct Teacher {
    std::string ID;
	bool pathway_one = false;          //does the teacher require a resarch day, (If it is false then they dont have a research day)
	std::vector<int> activities;       //Activities the teacher is teaching
	std::vector<int> bad_timeslots;    //timeslots the teacher is not free during
	
	std::string to_string();
};

class Teachers {
public:

	Teachers();
	Teacher& operator[](const int& a);

	bool is_bad_timeslot(const int& t, const int& ts);

	int size();
	std::string to_string();


private:
	std::vector<Teacher> data;

};