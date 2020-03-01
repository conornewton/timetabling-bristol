#include "Activities.hpp"
#include "Data.hpp"

#include "Students.hpp"
#include "Teachers.hpp"
#include "Rooms.hpp"

#include "../CSV/CSV.hpp"
#include "../Optimization/Objective.hpp"

#include "../Backtracking/HardConstraints.hpp"

#include <sstream>
#include <random>


std::string Activity::to_string(Rooms& r) {
    std::stringstream s;

    s << ID << ", " << name << ", " << type << ", " << dept << ", " << number_of_hours << ", " << timeslot << ", " << room << ", " << students.size() << std::endl;

    return s.str();
}

std::string Activities::to_string(Rooms& r) {
    std::stringstream s;

    for (Activity& a: data) {
        s << a.to_string(r);
    }
    return s.str();
}

Activities::Activities(Students& s, Teachers& t, Rooms& r) : data(), soft_clash_matrix(0), hard_clash_matrix(false), timetable(NO_TS, r.size()), hours_per_day(t.size(), 5) {
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

    std::cout << "Activities loaded" << std::endl;

    //Here we enroll students on there activities
    for (int i = 0; i < s.size(); i++) {
        Student& st = s[i];

        for (int activity : st.activities) {
            data[activity].students.push_back(i);
        }
    }

    std::cout << "Enrolling complete" << std::endl;

    //We also enroll the staff on there activities
    for (int i = 0; i < t.size(); i++) {
        Teacher& st = t[i];

        for (int activity : st.activities) {
            data[activity].teachers.push_back(i);
        }
    }

    std::cout << "staff enrolling complete" << std::endl;

    for (int i = 0; i < s.size(); i++) {
        Student& stu = s[i];
		for (unsigned int course_index1 : stu.activities) {
			for (unsigned int course_index2 : stu.activities) {
				if (course_index1 != course_index2) {
					soft_clash_matrix.set(course_index1, course_index2, soft_clash_matrix.get(course_index1, course_index2) + 1);
				}
			}
		}
	}

    for (int i = 0; i < t.size(); i++) {
        Teacher& tea = t[i];
		for (unsigned int course_index1 : tea.activities) {
			for (unsigned int course_index2 : tea.activities) {
				if (course_index1 != course_index2) {
					hard_clash_matrix.set(course_index1, course_index2, true);
				}
			}
		}
	}

    //Here we update the preferred rooms for the activities
    for (int i = 0; i < r.size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            if (r[i].Capacity >= data[j].students.size() - data[j].students.size()/4) data[j].preferred_rooms.push_back(i);
        }
    }

    blame.resize(data.size());

    timetable.set_all(-1);
    hours_per_day.set_all(0);
}

Activity& Activities::operator[](const int& a) {
    return data[a];
}

int Activities::soft_clash(const int& a, const int& b) {
    return soft_clash_matrix.get(a, b);
}

bool Activities::hard_clash(const int& a, const int& b) {
    return hard_clash_matrix.get(a, b);
}

int Activities::get(const int& timeslot, const int& room) {
    return timetable[timeslot][room];
} 

void Activities::set(const int& activity, int& timeslot, int& room) {

    timetable.set_n(timeslot, room, activity, data[activity].number_of_hours);
    
    data[activity].room = room;
    data[activity].timeslot = timeslot;

    
    for (int& teach : data[activity].teachers) {
        hours_per_day.set(teach, day_of_week(timeslot), hours_per_day.get(teach, day_of_week(timeslot)) + data[activity].number_of_hours);
    }
}

void Activities::unset(const int& activity) {
    timetable.set_n(data[activity].timeslot, data[activity].room, -1, data[activity].number_of_hours);

    for (int& teach : data[activity].teachers) {
        hours_per_day.set(teach, day_of_week(data[activity].timeslot), hours_per_day.get(teach, day_of_week(data[activity].timeslot)) - data[activity].number_of_hours);
    }

    data[activity].room = -1;
    data[activity].timeslot = -1;
}

//TOOO: make sure contraints are satisfied
//TODO: consider multi hour courses!
void Activities::simple_swap(const int& ts1, const int& rm1, const int& ts2, const int& rm2, Rooms& r, Teachers& t, Students& s) {
    int course1 = timetable.get(ts1, rm1);
    int course2 = timetable.get(ts2, rm2);

    timetable.set(ts1, rm1, course2);
    timetable.set(ts2, rm2, course1);

    if (course1 != -1) {
        data[course1].timeslot = ts2;
        data[course1].room = rm2;
        
        
        for (int& teach : data[course1].teachers) {
            hours_per_day.set(teach, day_of_week(ts2), hours_per_day.get(teach, day_of_week(ts2)) + data[course1].number_of_hours);
            hours_per_day.set(teach, day_of_week(ts1), hours_per_day.get(teach, day_of_week(ts1)) - data[course1].number_of_hours);
        }
    
    }

    if (course2 != -1) {
        data[course2].timeslot = ts1;
        data[course2].room = rm1;

        for (int& teach : data[course2].teachers) {
            hours_per_day.set(teach, day_of_week(ts2), hours_per_day.get(teach, day_of_week(ts2)) - data[course2].number_of_hours);
            hours_per_day.set(teach, day_of_week(ts1), hours_per_day.get(teach, day_of_week(ts1)) + data[course2].number_of_hours);
        }

    }

    update_blame(ts1, r, t, s);
    update_blame(ts2, r, t, s);
}

void Activities::kempe_swap(const int& ts1, const int& rm1, const int& ts2, const int& rm2, Rooms& r, Teachers& t, Students& s) {
    int activity1 = get(ts1, room1);
    int activity2 = get(ts2, room2);

    

}


int Activities::size() {
    return data.size();
}

void Activities::update_blame(const int& ts, Rooms& r, Teachers& t, Students& s) {

    for (int i = 0; i < r.size(); i++) {
        int a = get(ts, i);

        if (a != -1) blame[a] = objective_activity(*this, a, r, t, s);
    }
}

void Activities::update_blame_all(Rooms& r, Teachers& t, Students& s) {
    for (int i = 0; i < data.size(); i++) {
         blame[i] = objective_activity(*this, i, r, t, s);
    }
}

int Activities::objective() {
    int sum = 0;
    for (int& n : blame) sum += n;
    return sum;
}

int Activities::blame_activity() {
    static std::random_device rd;
	static std::mt19937 rng(rd());

	int blame_sum = 0;

	for (int i = 0; i < blame.size(); i++) {
		blame_sum += blame[i];
	}
	
	std::uniform_int_distribution<int> unif(0, blame_sum - 1);
	int r = unif(rng);

	for (int i = 0; i < blame.size(); i++) {
		if (r < blame[i]) return i;
		r -= blame[i];
	}

    return r;
}
int Activities::no_hours_per_day(const int& t, const int& day) {
    return hours_per_day.get(t, day);
}

int Activities::random_preferred_room(const int& a) {
    std::random_device rd1;
	std::mt19937 mt1(rd1());
    std::uniform_int_distribution<int> rand_room(0, data[a].preferred_rooms.size() - 1);

    return data[a].preferred_rooms[rand_room(mt1)];
}

//make sure teacher is free and not on pathway one
int Activities::random_timeslot(const int& a, Teachers& t) {
    std::random_device rd1;
	std::mt19937 mt1(rd1());
    std::uniform_int_distribution<int> rand_room(0, NO_TS - 1);

    int time;
    bool teachers_free;

    do {
        time = rand_room(mt1);

    } while(day_of_week(time) != day_of_week(time + data[a].number_of_hours) || !wednesday_afternoon_free(time, data[a].number_of_hours));

    return time;
}