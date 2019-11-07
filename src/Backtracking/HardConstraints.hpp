#include "../Data/Activities.hpp"

//time-related hard constraints
bool wednesday_afternoon_free(int ts);
bool teachers_free(Activities& a, Teachers& t, int ts, int activity);
bool teachers_pathway_one(Activities& a, Teachers& t, int ts, int activity);


//room-related hard constraints