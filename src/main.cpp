#include <iostream>

#include "Data/Students.hpp"
#include "Data/Rooms.hpp"
#include "Data/Teachers.hpp"
#include "Data/Activities.hpp"
   
//TODO: FIX THE DATA SO ITS EASIER TO LOAD
//We can do this by writing out the data from the other program
//Ideally we want to be using only four files


//TODO: every room appears to be bookable

int main() {

    //We use these containers for all of our data throughout
    Students s;
    Rooms r;
    Teachers t; 

    std::cout << r.to_string() << std::endl;

    //Activities a(s.size());

    return 0;
}
 