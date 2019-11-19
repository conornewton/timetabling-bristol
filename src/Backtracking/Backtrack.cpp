#include "Backtrack.hpp"

#include "HardConstraints.hpp"
#include "../Data/Data.hpp"
#include "../Data/Students.hpp"
#include "../Data/Rooms.hpp"
#include "../Data/Teachers.hpp"
#include "../Data/Activities.hpp"

#include <algorithm>

static std::vector<int> timeslots;

int next_room(Activities& a, Students& s, Teachers& t, Rooms& r, int activity, int timeslot) {

    for (int i = 0; i < r.size(); i++) {
        Room& room = r[i];
        if (room.Capacity > a[activity].students.size() && a.get(timeslot, i) == -1) {
            return i;
        }
    }

    return -1;
}

//we find the next timeslot we can use that will satisfy the hard constraints
//returns -1 if there is no available timeslot
int next_timeslot(Activities& a, Rooms& r, Students& s, Teachers& t, Matrix<bool>& bad_timeslots, int activity) {

    random_shuffle(timeslots.begin(), timeslots.end()); 

    for (int x : timeslots) {
        //should this be < or <= ??
        bool valid = !bad_timeslots[x][activity] && x + a[activity].number_of_hours <= NO_TS/5;

        for (int h = 0; h < a[activity].number_of_hours; h++) {
            int ts = x + h;

            valid &= wednesday_afternoon_free(ts) && no_hard_clash(a, r, activity, ts) && teachers_no_bad_timeslots(a, t, ts, activity) && teachers_pathway_one_day_off(a, t, ts, activity);
        }

        if (valid) return x;
	}

    return -1;
}

bool backtrack(Activities& a, Students& s, Teachers& t, Rooms& r) {

	for (int i = 0; i < NO_TS; i++) timeslots.push_back(i); //can i do this at compile time?

    int activity_index = 0;

    //TS x Activity Matrix
    Matrix<bool> bad_timeslots(NO_TS, a.size());
    bad_timeslots.set_all(false);

    while (activity_index < a.size()) {

        std::cout << activity_index << "\n";

        int timeslot = next_timeslot(a, r, s, t,bad_timeslots, activity_index);
        
        if (timeslot == -1) {
            //could not find a solution
            if (activity_index == 0) {
                return false;
            }

            //backtrack here
            bad_timeslots.set_row(activity_index, false);
            activity_index--;
            a.unset(activity_index);


        } else {
            int room = next_room(a, s, t, r, activity_index, timeslot);

            if (room == -1) {
                //choose a different timeslot
                bad_timeslots.set(timeslot, activity_index, true);

            } else {
                //we have found a new timeslot room pair!
                a.set(activity_index, timeslot, room);
                activity_index++;
            }
        }

    }

    return true;
}

