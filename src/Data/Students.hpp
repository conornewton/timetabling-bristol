#pragma once

#include <vector>
#include <string>
#include <unordered_map>

struct Student {
    std::string ID;
    std::vector<int> activities;

    std::string to_string();
};

class Students {
public:
    Students();

    Student& operator[](const int& x);
    int size();

    std::string to_string();
    int id_to_index(const std::string& id);

private:
    std::vector<Student> data;
    std::unordered_map<std::string, int> id_to_index_map;
};