#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Students.hpp"
#include "Teachers.hpp"
#include "Rooms.hpp"

#include "../Matrices/SparseMatrix.hpp"
#include "../Matrices/Matrix.hpp"

struct Activity {
    std::string ID;
	std::string name;
	std::string type;                        //Lecture/Problem Class/Tutorial/Practical
	std::string dept;

	int number_of_hours = 1;                 //labs usually are longer than a single hour

	std::vector<int> students;               //list of all students enrolled on the course.
	std::vector<int> teachers;               //staff required for this course

	std::vector<int> preferred_rooms;        //these should be sorted in order of size

	int timeslot = -1;
	int room = -1;

	std::string to_string(Rooms& r);                                
};

class Activities {

public:
    Activities(Students& s, Teachers& t, Rooms& r);
    Activity& operator[] (const int& a);

	int  soft_clash(const int& a, const int& b);              //tells us the number of students on both activities a and b
	bool hard_clash(const int& a, const int& b);              //tells us whether courses a and b can be scheduled at the same time
	int  get(const int& timeslot, const int& room);           //tells us which course is taking place in the specified timeslot and room
	void set(const int& activity, int& timeslot, int& room);  //sets the timeslot and room of the specified activity

	void simple_swap(const int& ts1, const int& rm1, const int& ts2, const int& rm2, Rooms& r, Teachers& t, Students& s); //performs simple swap
	void kempe_swap(const int& ts1, const int& rm1, const int& ts2, const int& rm2, Rooms& r, Teachers& t, Students& s); //performs a kempe swap

	void unset(const int& activity);
	int size();

	void update_blame_all(Rooms& r, Teachers& t, Students& s);
	int objective();
	int blame_activity();

	int random_preferred_room(const int& a);
	int random_timeslot(const int& a, Teachers& t);

	int no_hours_per_day(const int& t, const int& day);

	std::string to_string(Rooms& r);

	std::vector<int> blame;

private:

	void update_blame(const int& a, Rooms& r, Teachers& t, Students& s);

    std::vector<Activity> data;

	SparseMatrix<int> soft_clash_matrix;
	SparseMatrix<bool> hard_clash_matrix;

	Matrix<int> timetable;
	Matrix<char> hours_per_day;
};