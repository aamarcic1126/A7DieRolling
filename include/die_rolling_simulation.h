#ifndef DIE_ROLLING_SIMULATION_H
#define DIE_ROLLING_SIMULATION_H

#include <vector>
#include <chrono>
#include <iostream>
#include <random>

std::vector<int> roll_random_die(int times);
double get_time(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);
void print(std::vector<int> freq, double time);

#endif //DIE_ROLLING_SIMULATION_H
