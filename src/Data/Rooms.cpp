#include <Data/Rooms.hpp>

Rooms::Rooms() {

}

Room& Rooms::operator[](const int& a) {
    return data[a];
}