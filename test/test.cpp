#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "die_rolling_simulation.h"
#include <chrono>
#include <vector>
#include <numeric>
#include <random>

// You should include your implementation file or declare the tested functions
std::vector<int> roll_random_die(int times);
double get_time(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);

TEST_CASE("roll_random_die returns correct size vector with proper counts", "[roll_random_die]") {
    int totalRolls = 10000;
    auto freq = roll_random_die(totalRolls);

    REQUIRE(freq.size() == 7);  // index 0 is unused

    int sum = std::accumulate(freq.begin() + 1, freq.end(), 0); // skip index 0
    REQUIRE(sum == totalRolls);

    for (int i = 1; i <= 6; ++i) {
        REQUIRE(freq[i] >= 0);  // frequency can't be negative
    }
}

TEST_CASE("get_time returns non-negative duration", "[get_time]") {
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto end = std::chrono::steady_clock::now();

    double elapsed = get_time(start, end);
    REQUIRE(elapsed >= 0.0);
    REQUIRE(elapsed >= 0.01);  // at least 10ms = 0.01s
}