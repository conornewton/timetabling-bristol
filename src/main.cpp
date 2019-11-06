#include <iostream>

#include "Data/Students.hpp"
#include "Data/Rooms.hpp"
#include "Data/Teachers.hpp"
#include "Data/Activities.hpp"

#include "Backtracking/Backtrack.hpp"

int main() {

    //We use these containers for all of our data throughout
    Students s;
    Rooms r;
    Teachers t; 
    Activities a(s.size()); //activities requires the number of students for a timetable matrix

    //Stage 1 - Bactracking
    if (backtrack(a, s, t, r)) {
        //Stage 2 - Optimization
        
    } else {
        std::cout << "Finding an initial solution failed :(" << std::endl;
    }

    return 0;
}
 