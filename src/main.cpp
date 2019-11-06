#include <iostream>

#include "Data/Students.hpp"
#include "Data/Rooms.hpp"
#include "Data/Teachers.hpp"
#include "Data/Activities.hpp"

#include "Backtracking/Backtrack.hpp"
   
//TODO: FIX THE DATA SO ITS EASIER TO LOAD
//We can do this by writing out the data from the other program
//Ideally we want to be using only four files

//Room loading is complete

int main() {

    //We use these containers for all of our data throughout
    Students s;
    Rooms r;
    Teachers t; 
    Activities a(s.size()); //activities requires the number of students for a timetable matrix


    for (int i = 0; i < r.size(); i++) {
        Room room = r[i];
        std::cout << room.to_string() << std::endl;
    }


    if (backtrack(a, s, t, r)) {
        //Stage 2 - Optimization Here
        
    } else {
        std::cout << "Finding an initial solution failed :(" << std::endl;
    }

    return 0;
}
 