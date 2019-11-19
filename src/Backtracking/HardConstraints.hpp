#pragma once

#include "../Data/Activities.hpp"

//time-related hard constraints
bool wednesday_afternoon_free(const int& ts, const int& duration);
bool no_hard_clash(Activities& a, Rooms& r, const int& activity, const int& ts);
bool teachers_pathway_one_day_off(Activities& a, Teachers& t, const int& ts, const int& activity);
bool teachers_no_bad_timeslots(Activities& a, Teachers& t, const int& ts, const int& activity);

//room-related hard constraints
bool room_free(Activities& a, const int& ts, const int& rm, const int& activity);