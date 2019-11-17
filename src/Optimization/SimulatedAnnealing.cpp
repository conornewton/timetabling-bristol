#include "SimulatedAnnealing.hpp"
#include "Objective.hpp"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>

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

    const double initial_temp = 100;
	const double final_temp = 1;
	const double cooling_rate = 0.999;

	double current_temp = initial_temp;


    while (current_temp > final_temp) {

        current_temp *= cooling_rate;
    }
}