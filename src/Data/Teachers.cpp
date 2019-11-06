#include "Teachers.hpp"

#include "../CSV/CSV.hpp"
#include "Data.hpp"

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


int Teachers::id_to_index(const std::string& id) {
	auto search = id_to_index_map.find(id);

	if (search != id_to_index_map.end()) {
		return search->second;
	}

	return -1;
}