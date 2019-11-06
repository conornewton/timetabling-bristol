#include "Rooms.hpp"

Rooms::Rooms() {
}

Room& Rooms::operator[](const int& a) {
    return data[a];
}

int Rooms::size() {
    return data.size();
}