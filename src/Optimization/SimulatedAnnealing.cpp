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
	
	return (new_score < current_score || unif() < std::exp(((double)current_score - new_score) / temp));
}

void simmulated_annealing(Activities& a, Rooms& r, Students& s, Teachers& t) {

    const double initial_temp = 300;
	const double final_temp = 100;
	const double cooling_rate = 0.99999;

	double current_temp = initial_temp;

	a.update_blame_all(r, t, s);
	int current_score = a.objective();

    while (current_temp > final_temp) {
		std::cout << current_score << std::endl;

		int activity1 = a.blame_activity();

		//deal with this later
		if (a[activity1].number_of_hours > 1) continue;

		int room1 = a[activity1].room;
		int time1 = a[activity1].timeslot;

		
		int room2 = a.random_preferred_room(activity1);
		int time2;

		do {
			time2 = a.random_timeslot(activity1, t); 
		} while(a.get(time2, room2) != -1 && a[a.get(time2, room2)].number_of_hours > 1); //dont let this be a part of a multihour course!!!!

		a.simple_swap(time1, room1, time2, room2, r, t, s);

		int new_score = a.objective();

		if (!acceptance(current_score, new_score, current_temp)) {
			//we undo the swap if it is not accepted
			a.simple_swap(time1, room1, time2, room2, r, t, s);

			//TODO: here we try a kempe swap:
			//a.kempe_swap(time1, room1, time2, room2, t, s);

		} else {
			current_score = new_score;
			
		}
        current_temp *= cooling_rate;
    }
}