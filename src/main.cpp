#include <iostream>
#include <chrono>

#include "Data/Students.hpp"
#include "Data/Rooms.hpp"
#include "Data/Teachers.hpp"
#include "Data/Activities.hpp"

#include "Backtracking/Backtrack.hpp"

#include "Optimization/SimulatedAnnealing.hpp"
#include "Optimization/Objective.hpp"

//TODO: add lecturer hours they cant make
//TODO: fix multiple hour courses
//TODO: loop through preferred activities instead.

int main() {

    //We use these containers for all of our data throughout
    Students s;
    Rooms r;
    Teachers t; 
    Activities a(s, t);

    //Stage 1 - Bactracking
    if (backtrack(a, s, t, r)) {
        //Stage 2 - Optimization
        std::cout << "Stage 1 - Backtracking Complete :)" << std::endl;
        std::cout << "Stage 2 - Optimization Starting :)" << std::endl;

        int score = objective(a, r, t, s);

        std::cout << "Initial Score: " << score << std::endl;

        simmulated_annealing(a, r, s, t);

        std::cout << "Optimization Complete" << std::endl;

        score = objective(a, r, t, s);
        std::cout << "Final Score: " << score << std::endl;

    } else {
        std::cout << "Finding an initial solution failed :(" << std::endl;
    }

    return 0;
}
 