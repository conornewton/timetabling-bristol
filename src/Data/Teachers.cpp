#include "Teachers.hpp"

#include "../CSV/CSV.hpp"
#include "Data.hpp"

#include <sstream>

std::string Teacher::to_string() {
	std::stringstream s;

	s << ID << ", ";

	for (int a : activities) {
		s << a << " ";
	}

	s << pathway_one << ", ";

	for (int t : bad_timeslots) {
		s << t << " ";
	}

	return s.str();
}

std::string Teachers::to_string() {
	std::stringstream s;

	for (Teacher& t: data) {
		s << t.to_string();
		s << "\n";
	}

	return s.str();
}

Teachers::Teachers() {
    CSV csv_staff(FILEPATH_TEACHERS);

	while (csv_staff.next_line()) {
		auto values = csv_staff.get_values();

        Teacher t;
        t.ID = values[0];

		std::vector<std::string> activity_values = split(values[1], ',');
		for (int i = 0; i < activity_values.size(); i++) {
			t.activities.push_back(stoi(activity_values[i]));
		}

		if (values[2][0] == '1') {
			t.pathway_one = true;
		} else {
			t.pathway_one = false;
		}

		std::vector<std::string> timeslot_values = split(values[3], ',');
		for (int i = 0; i < timeslot_values.size(); i++) {
			t.bad_timeslots.push_back(stoi(timeslot_values[i]));
		}

		data.push_back(t);
	}
}

Teacher& Teachers::operator[](const int& a) {
    return this->data[a];
}

int Teachers::size() {
    return data.size();
}


int Teachers::id_to_index(const std::string& id) {
	auto search = id_to_index_map.find(id);

	if (search != id_to_index_map.end()) {
		return search->second;
	}

	return -1;
}