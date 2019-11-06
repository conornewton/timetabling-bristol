#include "Activities.hpp"
#include "Data.hpp"

#include "../CSV/CSV.hpp"

#include <sstream>


std::string Activity::to_string() {
    std::stringstream s;

    s << ID << ", " << name << ", " << type << ", " << dept << ", " << number_of_hours << std::endl;

    return s.str();
}

std::string Activities::to_string() {
    std::stringstream s;

    for (Activity& a: data) {
        s << a.to_string();
    }
    return s.str();
}

Activities::Activities(const int& no_rooms) : data(), soft_clash_matrix(-1), hard_clash_matrix(false), timetable(NO_TS, no_rooms) {
    CSV csv_activities(FILEPATH_ACTIVITIES);

	while (csv_activities.next_line()) {
		std::vector<std::string> values = csv_activities.get_values();
        
        Activity a;
        a.ID = values[0];
        a.name = values[1];
        a.type = values[2];
        a.dept = values[3];

        //std::cout << values[4] << std::endl;
        a.number_of_hours = stoi(values[4]);

		data.push_back(a);
	}

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

int Activities::size() {
    return data.size();
}

int Activities::id_to_index(const std::string& id) {
	auto search = id_to_index_map.find(id);

	if (search != id_to_index_map.end()) {
		return search->second;
	}

	return -1;
}

