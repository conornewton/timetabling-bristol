#include <Data/Activities.hpp>

#include "Data.hpp"

Activities::Activities(const int& no_rooms) : data(), soft_clash_matrix(-1), hard_clash_matrix(false), timetable(NO_TS, no_rooms) {
    
}

Activity& Activities::operator[](const int& a) {
    return data[a];
}

int Activities::soft_clash(const int& a, const int& b) {
    return soft_clash_matrix.get(a, b);
}

bool Activities::hard_clash(const int& a, const int& b) {
    return soft_clash_matrix.get(a, b);
}

int Activities::get(const int& timeslot, const int& room) {
    return timetable[timeslot][room];
} 

void Activities::set(const int& activity, int& timeslot, int& room) {
    timetable.set(timeslot, room, activity);
}

