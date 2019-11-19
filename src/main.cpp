#include <iostream>
#include <chrono>
#include <time.h>
#include <random>

#include "Data/Students.hpp"
#include "Data/Rooms.hpp"
#include "Data/Teachers.hpp"
#include "Data/Activities.hpp"

#include "Backtracking/Backtrack.hpp"

#include "Optimization/SimulatedAnnealing.hpp"
#include "Optimization/Objective.hpp"

#include "Backtracking/HardConstraints.hpp"

//TODO: implement Kempe swaps

//TODO: add lunch break soft constraint
//TODO: find out why backtracking cannot do hard clashes

int main() {

    srand(time(NULL));

    //We use these containers for all of our data throughout
    Students s;
    Rooms r;
    Teachers t; 
    Activities a(s, t, r);


    //Stage 1 - Bactracking
    if (backtrack(a, s, t, r)) {
        //Stage 2 - Optimization
        std::cout << "Stage 1 - Backtracking Complete :)" << std::endl;
        std::cout << "Stage 2 - Optimization Starting :)" << std::endl;

        int score = objective(a, r, t, s);
      
        std::cout << "Initial Score: " << score << std::endl;
        objective_print(a, r, t, s);

        auto start = std::chrono::high_resolution_clock::now();
        simmulated_annealing(a, r, s, t);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

        std::cout << "Optimization Complete (" << duration.count() << ")" << std::endl;

        score = objective(a, r, t, s);
        std::cout << "Final Score: " << score << std::endl;
        objective_print(a, r, t, s);
        std::cout << a.objective() << std::endl;

    } else {
        std::cout << "Finding an initial solution failed :(" << std::endl;
    }

    return 0;

}
 