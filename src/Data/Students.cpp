#include "Data/Students.hpp"

Students::Students() {
    
}

Student& Students::operator[](const int& x) {
    return this->data[x];
}

const int Students::size() {
    return data.size();
}