#include "Objective.hpp"

#include "../Data/Data.hpp"

#include <iostream>

constexpr int w1 = 2;
constexpr int w2 = 1;
constexpr int w3 = 20;
constexpr int w4 = 20;
constexpr int w5 = 20;

int capacity_weight(Activity& a, Rooms& r) {
	int score = 0;

    int room_size = r[a.room].Capacity;

	if (a.students.size() > room_size) {
		score += a.students.size() - room_size;
    }

	return score;
}

int soft_clashes_score(Activities& as, int a) {
    int score = 0;

	for (int b = 0; b < as.size(); b++) {

		if (b != a && as[a].timeslot == as[b].timeslot) {
			score += as.soft_clash(a, b);
		}
	}
	
	return score;
}

int hard_clashes_score(Activities& as, int a) {
    int score = 0;

	for (int b = 0; b < as.size(); b++) {
		if (b != a && as[a].timeslot == as[b].timeslot) {
            if (as.hard_clash(a, b)) score += 1;
		}
	}
	
	return score;
}

int wednesday_afternoon_free(Activity& a) {

    int hours_per_day = NO_TS / 5;
    if (a.timeslot < hours_per_day * 2 + 5 || a.timeslot >= hours_per_day * 3) {
        return 1;
    }

    return 0;
}


bool teachers_pathway_one_day_off(Activities& a, Teachers& t, int activity) {
    int score = 0;

    Activity& act = a[activity];

    for (int teacher : act.teachers) {
       if (t[teacher].pathway_one) {

			if (a.no_hours_per_day(teacher, 0) != 0 
                && a.no_hours_per_day(teacher, 1) != 0 
                && a.no_hours_per_day(teacher, 2) != 0
                && a.no_hours_per_day(teacher, 3) != 0
                && a.no_hours_per_day(teacher, 4) != 0) {
				score += 1; //TODO: make this the minimum of the hours per day
			}
		}
    }

    return score;
}

int objective_activity(Activities& as, const int& a, Rooms& r, Teachers& t, Students& s) {
    return w1 * capacity_weight(as[a], r) + w2 * soft_clashes_score(as, a) + w3 * hard_clashes_score(as, a) + w4 * wednesday_afternoon_free(as[a]) + w5 * teachers_pathway_one_day_off(as, t, a);
}


int objective(Activities& a, Rooms& r, Teachers& t, Students& s) {
    int score = 0;

    for (int i = 0; i < a.size(); i++) {
        score += objective_activity(a, i, r, t, s);
    }

    return score;
}