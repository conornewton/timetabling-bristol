#include "HardConstraints.hpp"

#include "../Data/Data.hpp"

bool wednesday_afternoon_free(int ts) {
    int hours_per_day = NO_TS / 5;
	return ts < hours_per_day * 2 + 5 || ts >= hours_per_day * 3;
}

bool teachers_free(Activities& a, Teachers& t, int ts, int activity) {
    Activity& act = a[activity];

    for (int teacher : act.teachers) {
        if (!t.is_free(a, teacher, ts)) return false;
    }
    return true;
}

bool teachers_pathway_one(Activities& a, Teachers& t, int ts, int activity) {
    Activity& act = a[activity];

    for (int teacher : act.teachers) {
        if (t[teacher].pathway_one) {
            //make sure they have a full day off
        }
    }
}