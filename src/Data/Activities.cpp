#include "Activities.hpp"
#include "Data.hpp"

#include "Students.hpp"
#include "Teachers.hpp"
#include "Rooms.hpp"

#include "../CSV/CSV.hpp"

#include <sstream>


std::string Activity::to_string(Rooms& r) {
    std::stringstream s;

    s << ID << ", " << name << ", " << type << ", " << dept << ", " << number_of_hours << ", " << timeslot << ", " << r[room].Name << std::endl;

    return s.str();
}

std::string Activities::to_string(Rooms& r) {
    std::stringstream s;

    for (Activity& a: data) {
        s << a.to_string(r);
    }
    return s.str();
}

Activities::Activities(Students& s, Teachers& t) : data(), soft_clash_matrix(-1), hard_clash_matrix(false), timetable(NO_TS, s.size()), teacher_timetable(-1), teacher_timetable(-1) {
    //First load course data from CSV's
    CSV csv_activities(FILEPATH_ACTIVITIES);

	while (csv_activities.next_line()) {
		std::vector<std::string> values = csv_activities.get_values();
        
        Activity a;
        a.ID = values[0];
        a.name = values[1];
        a.type = values[2];
        a.dept = values[3];

        //std::cout << values[4] << std::endl;
        a.number_of_hours = stoi(values[4]);

		data.push_back(a);
	}

    //Here we enroll students on there activities
    for (int i = 0; i < s.size(); i++) {
        Student& st = s[i];

        for (int activity : st.activities) {
            data[activity].students.push_back(i);
        }
    }

    //We also enroll the staff on there activities
    for (int i = 0; i < t.size(); i++) {
        Teacher& st = t[i];

        for (int activity : st.activities) {
            data[activity].teachers.push_back(i);
        }
    }

    //Here we update the preferred rooms for the activities
}

Activity& Activities::operator[](const int& a) {
    return data[a];
}

int Activities::soft_clash(const int& a, const int& b) {
    return soft_clash_matrix.get(a, b);
}

bool Activities::hard_clash(const int& a, const int& b) {
    return soft_clash_matrix.get(a, b);
}

int Activities::get(const int& timeslot, const int& room) {
    return timetable[timeslot][room];
} 

void Activities::set(const int& activity, int& timeslot, int& room) {
    timetable.set(timeslot, room, activity);
    data[activity].room = room;
    data[activity].timeslot = timeslot; 
}

void Activities::unset(const int& activity) {
    timetable.set(data[activity].timeslot, data[activity].room, -1);
    data[activity].room = -1;
    data[activity].timeslot = -1;
}

int Activities::size() {
    return data.size();
}