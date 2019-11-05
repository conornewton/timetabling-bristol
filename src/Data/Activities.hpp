#pragma once

#include <string>
#include <vector>

#include "SparseMatrix/SparseMatrix.hpp"

class Activity {
    std::string ID;
	std::string name;
	std::string type;                        //Lecture/Problem Class/Tutorial/Practical

	int module;                              //index of the Module that this lecture is a part of

	int number_of_hours = 1;                 //labs usually are longer than a single hour

	std::vector<int> students;               //list of all students enrolled on the course.
	std::vector<int> staff;                  //staff required for this course

	std::vector<int> preferred_rooms;        //these should be sorted in order of size

	int timeslot = -1;
	int room = -1;                                
};

class Activities {

public:
    Activities();
    Activity& operator[] (const int& a);

	int  soft_clash_score(const int& a, const int& b); //tells us the number of students on both activities a and b
	bool hard_clash(const int& a, const int& b);       //tells us whether courses a and b can be scheduled at the same time.

private:
    std::vector<Activity> data;
	SparseMatrix<int> soft_clashes;
	SparseMatrix<bool> hard_clashes;
};