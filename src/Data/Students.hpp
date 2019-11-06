#pragma once

#include <vector>
#include <string>

struct Student {
    std::string ID;
    std::vector<int> activities;

    std::string to_string();
};

class Students {
public:
    Students();

    Student& operator[](const int& x);
    const int size();

    std::string to_string();

private:
    std::vector<Student> data;
    
};