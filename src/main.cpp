#include "die_rolling_simulation.h"
#include <thread>
#include <future>

int main() {
    // -----------------------------------------------
    // 1. SINGLE-THREADED VERSION
    // -----------------------------------------------

    auto start = std::chrono::steady_clock::now();
    auto freq = roll_random_die(60'000'000);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Single-threaded version:\n";
    print(freq, get_time(start, end));


    // -----------------------------------------------
    // 2. MULTI-THREADED with std::launch::async
    // -----------------------------------------------

    auto nCores = std::thread::hardware_concurrency(); // Get number of CPU cores
    int rollsPerThread = 60'000'000 / (int)nCores;     // Divide workload per thread

    // Launch each task immediately in a new thread
    std::vector<std::future<std::vector<int>>> async_futures;
    auto async_start = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < nCores; i++) {
        async_futures.push_back(std::async(std::launch::async, roll_random_die, rollsPerThread));
    }

  // Combine results from async futures
    std::vector<int> freqCounter_async(7, 0);
    for (auto& fut : async_futures) {
        auto partial = fut.get();
        for (int i = 0; i < 7; i++) {
            freqCounter_async[i] += partial[i];
        }
    }

    auto async_end = std::chrono::steady_clock::now();

    std::cout << "\nMulti-threaded with std::launch::async:\n";
    print(freqCounter_async, get_time(async_start, async_end));


    // -----------------------------------------------
    // 3. MULTI-THREADED with std::launch::deferred
    // -----------------------------------------------

    std::vector<std::future<std::vector<int>>> deferred_futures;

    auto deferred_start = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < nCores; ++i) {
        deferred_futures.push_back(std::async(std::launch::deferred, roll_random_die, rollsPerThread));
    }

    std::vector<int> freqCounter_deferred(7, 0);
    for (auto& fut : deferred_futures) {
        auto partial = fut.get();
        for (int i = 1; i <= 6; ++i)
            freqCounter_deferred[i] += partial[i];
    }

    auto deferred_end = std::chrono::steady_clock::now();

    std::cout << "\nMulti-threaded with std::launch::deferred:\n";
    print(freqCounter_deferred, get_time(deferred_start, deferred_end));

    return 0;
}

// -----------------------------------------------
// Summary (Paste your actual output as comment) in the code:
// -----------------------------------------------
/*

Single-threaded version:
10002443 10002892 9998405 9995838 10000319 10000103 : 1.99 seconds

Multi-threaded with std::launch::async:
9998321 9999323 10001184 10002461 10001254 9997457 : 0.274 seconds

Multi-threaded with std::launch::deferred:
10001337 9997174 10006413 9993852 9999605 10001619 : 1.909 seconds

*/