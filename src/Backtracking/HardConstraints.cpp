#include "HardConstraints.hpp"

#include "../Data/Data.hpp"

#include <iostream>

bool wednesday_afternoon_free(int ts) {
    int hours_per_day = NO_TS / 5;
	return ts < hours_per_day * 2 + 5 || ts >= hours_per_day * 3;
}

//TODO: can i make this faster?
bool no_hard_clash(Activities& a, Rooms& rs, const int& activity, const int& ts) {
    for (int r = 0; r < rs.size(); r++) {
        int b = a.get(ts, r);
        if (b != -1 && a.hard_clash(activity, b)) {
            return false;
        }
    }
    return true;
}

int day_of_week(int timeslot) {
	int hours_per_day = NO_TS / 5;

	if (timeslot < hours_per_day) return 0;
	if (timeslot < hours_per_day * 2) return 1;
	if (timeslot < hours_per_day * 3) return 2;
	if (timeslot < hours_per_day * 4) return 3;
	if (timeslot < hours_per_day * 5) return 4;
	return -1;
}

bool teachers_pathway_one_day_off(Activities& a, Teachers& t, int ts, int activity) {
    Activity& act = a[activity];

    for (int teacher : act.teachers) {
       if (t[teacher].pathway_one) {
			std::array<bool, 5> days;
			days.fill(false);

			days[day_of_week(ts)] = true;

			for (int a_index : t[teacher].activities) {
				const Activity& act = a[a_index];			
				days[day_of_week(act.timeslot)] = true;
			}

			if (days[0] && days[1] && days[2] && days[3] && days[4]) {
				return false;
			}
		}
    }

    return true;
}

bool teachers_no_bad_timeslots(Activities& a, Teachers& t, int ts, int activity) {
    for (int teach : a[activity].teachers) {
        if (t.is_bad_timeslot(teach, ts)) return false;
    }

    return true;
}