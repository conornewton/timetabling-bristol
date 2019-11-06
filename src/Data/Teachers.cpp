#include "Teachers.hpp"

Teachers::Teachers() {
    CSV csv_staff(FILEPATH_STAFF);

	while (csv_staff.next_line()) {
		auto values = csv_staff.get_values();

        Teacher t;
        t.ID = values[0];

		data.push_back(t);
	}
}

Teacher& Teachers::operator[](const int& a) {
    return this->data[a];
}

int Teachers::size() {
    return data.size();
}