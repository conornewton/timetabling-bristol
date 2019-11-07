#include "Students.hpp"

#include "Data.hpp"
#include "../CSV/CSV.hpp"

#include <unordered_map>
#include <sstream>
#include <iostream>

std::string Student::to_string() {
	std::stringstream s;
	s << "ID: " << ID << "\nActivities: ";
	for (int a : activities) {
		s << a << ", ";
	}

	return s.str();
}

std::string Students::to_string() {
	std::stringstream s;

	for (Student& st: data) {
		s << st.to_string();
		s << "\n";
	}

	return s.str();
}

Students::Students() {
    CSV csv_students(FILEPATH_STUDENTS);

	while (csv_students.next_line()) {
		auto values = csv_students.get_values();

		Student s;
		s.ID = values[0];
		
		std::vector<std::string> activity_values = split(values[1], ',');

		for (int i = 0; i < activity_values.size(); i++) {
			s.activities.push_back(stoi(activity_values[i]));
		}
		
		data.push_back(s);
	}
}

Student& Students::operator[](const int& x) {
    return this->data[x];
}

int Students::size() {
    return data.size();
}

int Students::id_to_index(const std::string& id) {
	auto search = id_to_index_map.find(id);

	if (search != id_to_index_map.end()) {
		return search->second;
	}

	return -1;
}