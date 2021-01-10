// Demonstrate std::execution policies for parallel and/or vectorized sorting.
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <ratio>

template <typename ExecutionPolicy>
double timeit_sort(ExecutionPolicy&& policy)
{
    using T = std::uint64_t;

    // Allocate vector of 1e6 elements.
    std::size_t nelems = 1'000'000;
    std::vector<T> nums(nelems);
    std::iota(std::begin(nums), std::end(nums), T(0));

    std::default_random_engine gen{};

    // Capture elapsed time based on nrepeat samples.
    std::size_t nrepeat = 10;
    std::vector<double> duration;
    duration.reserve(nrepeat);

    while (nrepeat > 0) {
        // Shuffle the input vector.
        std::shuffle(std::begin(nums), std::end(nums), gen);

        auto t1 = std::chrono::high_resolution_clock::now();
        std::sort(policy, std::begin(nums), std::end(nums));
        auto t2 = std::chrono::high_resolution_clock::now();
        duration.push_back(std::chrono::duration<double, std::milli>(t2-t1).count());

        --nrepeat;
    }

    // Compute the mean elapsed time, in ms.
    double sum = std::accumulate(std::begin(duration), std::end(duration), 0.);
    double mean = sum / duration.size();
    return mean;
}

int main()
{
    // Output:
    // 952.651 Sequential.
    // 652.404 Vectorized.
    // 503.684 Parallel.
    // 1004.08 Parallel and vectorized.
    std::cout << timeit_sort(std::execution::seq)       << " Sequential.\n";
    std::cout << timeit_sort(std::execution::unseq)     << " Vectorized.\n";
    std::cout << timeit_sort(std::execution::par)       << " Parallel.\n";
    std::cout << timeit_sort(std::execution::par_unseq) << " Parallel and vectorized.\n";
}
