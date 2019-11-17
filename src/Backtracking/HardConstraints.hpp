#include "../Data/Activities.hpp"

//time-related hard constraints
bool wednesday_afternoon_free(int ts);
bool no_hard_clash(Activities& a, Rooms& r, const int& activity, const int& ts);
bool teachers_pathway_one_day_off(Activities& a, Teachers& t, int ts, int activity);
bool teachers_no_bad_timeslots(Activities& a, Teachers& t, int ts, int activity);