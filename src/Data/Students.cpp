#include "Students.hpp"

#include "Data.hpp"
#include "../CSV/CSV.hpp"

#include <unordered_map>
#include <sstream>

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
    std::unordered_map<std::string, int> student_id_index;

    CSV csv_students(FILEPATH_STUDENTS);

	while (csv_students.next_line()) {
		auto values = csv_students.get_values();

		Student s;
		s.ID = values[0];

		data.push_back(s);
		student_id_index[values[0]] = data.size() - 1;
	}
}

Student& Students::operator[](const int& x) {
    return this->data[x];
}

const int Students::size() {
    return data.size();
}

int Students::id_to_index(const std::string& id) {
	auto search = id_to_index_map.find(id);

	if (search != id_to_index_map.end()) {
		return search->second;
	}

	return -1;
}