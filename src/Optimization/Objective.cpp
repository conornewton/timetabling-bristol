#include "Objective.hpp"

#include "../Data/Data.hpp"

#include <iostream>

constexpr int w1 = 10;
constexpr int w2 = 5;
constexpr int w3 = 100;
constexpr int w4 = 100;

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

	for (int b = a + 1; b < as.size(); b++) {
		if (as[a].timeslot == as[b].timeslot) {
			score += as.soft_clash(a, b);
		}
	}
	
	return score;
}


int hard_clashes_score(Activities& as, int a) {
    int score = 0;

	for (int b = a + 1; b < as.size(); b++) {
		if (as[a].timeslot == as[b].timeslot) {
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

int objective_activity_verbose(Activities& as, int a, Rooms& r, Teachers& t, Students& s) {

    std::cout << w1 * capacity_weight(as[a], r) << std::endl;
    std::cout << w2 * soft_clashes_score(as, a) << std::endl;
    std::cout << w3 * hard_clashes_score(as, a) << std::endl;
    std::cout << w4 * wednesday_afternoon_free(as[a]) << std::endl;

    return w1 * capacity_weight(as[a], r) + w2 * soft_clashes_score(as, a) + w3 * hard_clashes_score(as, a) + w4 * wednesday_afternoon_free(as[a]);
}

int objective_activity(Activities& as, int a, Rooms& r, Teachers& t, Students& s) {
    return w1 * capacity_weight(as[a], r) + w2 * soft_clashes_score(as, a) + w3 * hard_clashes_score(as, a) + w4 * wednesday_afternoon_free(as[a]);
}

int objective(Activities& a, Rooms& r, Teachers& t, Students& s) {
    int score = 0;

    for (int i = 0; i < a.size(); i++) {
        score += objective_activity(a, i, r, t, s);
    }

    return score;
}