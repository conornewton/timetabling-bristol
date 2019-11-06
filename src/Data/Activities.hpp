#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../Matrices/SparseMatrix.hpp"
#include "../Matrices/Matrix.hpp"

struct Activity {
    std::string ID;
	std::string name;
	std::string type;                        //Lecture/Problem Class/Tutorial/Practical
	std::string dept;

	int number_of_hours = 1;                 //labs usually are longer than a single hour

	std::vector<int> students;               //list of all students enrolled on the course.
	std::vector<int> staff;                  //staff required for this course

	std::vector<int> preferred_rooms;        //these should be sorted in order of size

	int timeslot = -1;
	int room = -1;

	std::string to_string();                                
};

class Activities {

public:
    Activities(const int& activities);
    Activity& operator[] (const int& a);

	int  soft_clash(const int& a, const int& b);              //tells us the number of students on both activities a and b
	bool hard_clash(const int& a, const int& b);              //tells us whether courses a and b can be scheduled at the same time
	int  get(const int& timeslot, const int& room);           //tells us which course is taking place in the specified timeslot and room
	void set(const int& activity, int& timeslot, int& room);  //sets the timeslot and room of the specified activity

	int size();

	int id_to_index(const std::string& id);

	std::string to_string();
	
private:
    std::vector<Activity> data;
	std::unordered_map<std::string, int> id_to_index_map;

	SparseMatrix<int> soft_clash_matrix;
	SparseMatrix<bool> hard_clash_matrix;
	Matrix<int> timetable;
};