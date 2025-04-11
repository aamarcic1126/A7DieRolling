#include "die_rolling_simulation.h"

using namespace std::chrono;

// Function to simulate rolling a six-sided die 'times' times.
// Returns a vector<int> where index i represents the frequency of die face i.
// Note: frequency[0] will be unused for convenience (so face 1 maps to index 1).

std::vector<int> roll_random_die(int times) {

	// Step 1: Set up a random number generator (seed, random enginer, uniform distribution etc)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution dist(1, 6);

	// Step 2: Initialize frequency vector of size 7 (index 0 unused)
	std::vector<int> frequencies(7, 0);
	frequencies[0] = 0;

	// Step 3: Roll the die 'times' times
	for (int i = 0; i < times; i++) {
		int roll = dist(gen);
		frequencies[roll]++;
	}

	// Step 4: Return the frequency vector
	return frequencies;
}

// Function to calculate elapsed time in seconds between two-time points
// Parameters:
//   - start: the starting time point
//   - end: the ending time point
// Returns:
//   - the duration in seconds as a double

double get_time(steady_clock::time_point start, steady_clock::time_point end) {

	// Step 1: Calculate the duration between 'end' and 'start' in milliseconds
	// milliseconds gives higher precision since directly computing seconds will truncate fractional
	auto time_ms = duration_cast<milliseconds>(end - start);

	// Step 2: Convert the duration to seconds (milliseconds to seconds)
	double time_s = time_ms.count() / 1000.0;

	// Step 3: Return the duration in seconds
	return time_s;
}

// Function to print the frequency of die rolls and the time taken to compute them
// Parameters:
//   - freq: a vector containing the frequency of each die face (index 1 to 6)
//   - time: the time duration in seconds (as a double) it took to perform the simulation

void print(std::vector<int> freq, double time) {

	// Loop through the frequency vector starting from index 1 (index 0 is unused)
	for (int i{ 1 }; i < freq.size(); i++)
		std::cout << freq[i] << " ";  // Print each frequency separated by a space

	// Print the total time taken after the frequencies
	std::cout << ": " << time << " seconds \n";
}

// Sample output:
// Each number corresponds to the frequency of die faces 1 to 6
// Time is shown after the colon
/*
10003111 10005348 10000549 10001391 9994485 9995116 : 2.034 seconds
9999281 10000895 9999485 9999850 9998419 10002070 : 0.171 seconds
*/