#include "SimulatedAnnealing.hpp"
#include "Objective.hpp"

#include "../Data/Data.hpp"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <time.h>

//returns a random number in the interval [0, 1)
inline double unif() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, 1);

	return dist(mt);
}

//probability acceptance function
inline bool acceptance(int current_score, int new_score, double temp) {

	return new_score < current_score;
	//return (new_score < current_score || unif() < std::exp(((double)current_score - new_score) / temp));
}

void simmulated_annealing(Activities& a, Rooms& r, Students& s, Teachers& t) {

    const double initial_temp = 1000;
	const double final_temp = 1;
	const double cooling_rate = 0.999;

	double current_temp = initial_temp;

	a.update_blame_all(r, t, s);

	srand(time(NULL));

    while (current_temp > final_temp) {
		int current_score = a.objective();

		//std::cout << current_score << std::endl;

		int activity1 = a.blame_activity();

		//std::cout << activity1 <<  "\n";

		int room1 = a[activity1].room;
		int time1 = a[activity1].timeslot;

		int room2 = rand() % r.size();
		int time2 = rand() % NO_TS;

		a.simple_swap(time1, room1, time2, room2, r, t, s);


		if (!acceptance(current_score, a.objective(), current_temp)) {
			
			//we undo the swap if it is not accepted
			a.simple_swap(time1, room1, time2, room2, r, t, s);
		}

        current_temp *= cooling_rate;
    }
}