#include "Data.hpp"

int day_of_week(int timeslot) {
	int hours_per_day = NO_TS / 5;

	if (timeslot < hours_per_day) return 0;
	if (timeslot < hours_per_day * 2) return 1;
	if (timeslot < hours_per_day * 3) return 2;
	if (timeslot < hours_per_day * 4) return 3;
	if (timeslot < hours_per_day * 5) return 4;
	return -1;
}