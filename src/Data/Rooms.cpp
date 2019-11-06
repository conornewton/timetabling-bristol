#include "Rooms.hpp"
#include "Data.hpp"
#include "../CSV/CSV.hpp"

#include <algorithm>
#include <sstream>


std::string Room::to_string() {
	std::stringstream s;

	s << "ID: " << Id << ", Name: " << Name << ", Dept: " << Dept << ", Capacity: " << Capacity << ", Bookable: " << Bookable;

	return s.str();
}

std::string Rooms::to_string() {
	std::stringstream s;
	for (Room& r: data) {
		s << r.to_string() << "\n";
	}
	return s.str();
}

bool room_compare(const Room& r1, const Room& r2) {
	return r1.Capacity < r2.Capacity;
}

Rooms::Rooms() {

	CSV csv_rooms(FILEPATH_ROOMS);

	while (csv_rooms.next_line()) {
		std::vector<std::string> values = csv_rooms.get_values();
        
        Room r;
        r.Id = values[0];
        r.Name = values[1];
        r.Dept = values[2];
        r.Capacity = std::stoi(values[3]);
        r.Bookable = true;

		if (values[4] == "0") {
			r.Bookable = false;
		}

		data.push_back(r);
	}

	sort(data.begin(), data.end(), room_compare);
}

Room& Rooms::operator[](const int& a) {
    return data[a];
}

int Rooms::size() {
    return data.size();
}

int Rooms::id_to_index(const std::string& id) {
	auto search = id_to_index_map.find(id);

	if (search != id_to_index_map.end()) {
		return search->second;
	}

	return -1;
}