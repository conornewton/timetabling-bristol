#include "Data/Students.hpp"

#include "Data.hpp"
#include "CSV/CSV.hpp"

#include <unordered_map>

Students::Students() {
    static std::unordered_map<std::string, int> student_id_index;

    CSV csv_students(FILEPATH_STUDENTS);

	while (csv_students.next_line()) {
		auto values = csv_students.get_values();
		students.push_back( {values[0]}) ;
		student_id_index[values[0]] = students.size() - 1;
	}

	CSV csv_enrollment(FILEPATH_ENROLEMENT);

	while (csv_enrollment.next_line()) {
		auto values = csv_enrollment.get_values();
		enroll_student(students, activities, values[0], values[1]);
	}
}

Student& Students::operator[](const int& x) {
    return this->data[x];
}

const int Students::size() {
    return data.size();
}