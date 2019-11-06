#pragma once

#include <vector>
#include <string>

class Student{
    std::string ID;
    std::vector<int> activities;
};

class Students {
public:
    Students();
    Student& operator[](const int& x);
    const int size();

private:
    std::vector<Student> data;
    
};