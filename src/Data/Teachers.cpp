#include "Data/Teachers.hpp"

Teachers::Teachers() {

}

Teacher& Teachers::operator[](const int& a) {
    return this->data[a];
}