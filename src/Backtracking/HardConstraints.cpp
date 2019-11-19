#include "HardConstraints.hpp"

#include "../Data/Data.hpp"

#include <iostream>

bool wednesday_afternoon_free(const int& ts, const int& duration) {
    int hours_per_day = NO_TS / 5;

    for (int i = ts; i < ts + duration; i++) {
        if (i >= hours_per_day * 2 + 5 && i < hours_per_day * 3) return false;
    }

	return true;
}


bool no_hard_clash(Activities& a, Rooms& rs, const int& activity, const int& ts) {
    int duration = a[activity].number_of_hours;

    for (int time = ts; time < ts + duration; time++) {
        for (int r = 0; r < rs.size(); r++) {
            int b = a.get(time, r);
            if (b != -1 && a.hard_clash(activity, b)) {
                return false;
            }
        }
    }
    
    return true;
}

//TODO: improve this function!!!!
bool teachers_pathway_one_day_off(Activities& a, Teachers& t, const int& ts, const int& activity) {
    Activity& act = a[activity];
    int duration = a[activity].number_of_hours;

    for (int time = ts; time < ts + duration; time++) {
        for (int teacher : act.teachers) {
            if (t[teacher].pathway_one) {
                std::array<bool, 5> days;
                days.fill(false);

                days[day_of_week(time)] = true;

                for (int a_index : t[teacher].activities) {
                    const Activity& act = a[a_index];			
                    days[day_of_week(act.timeslot)] = true;
                }

                if (days[0] && days[1] && days[2] && days[3] && days[4]) {
                    return false;
                }
            }
        }
    }
   

    return true;
}

bool teachers_no_bad_timeslots(Activities& a, Teachers& t, const int& ts, const int& activity) {
    int duration = a[activity].number_of_hours;
    for (int time = ts; time < ts + duration; time++) {
        for (int teach : a[activity].teachers) {
            if (t.is_bad_timeslot(teach, time)) return false;
        }
    }
    return true;
}


bool room_free(Activities& a, const int& ts, const int& rm, const int& activity) {
    for (int h = 0; h < a[activity].number_of_hours; h++) {
        if (a.get(ts + h, rm) != -1) return false;
    }

    return true;
}