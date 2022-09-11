// Demonstrate use of pseudorandom number generators in std::random.
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

double chisq_vec(const std::vector<int>& hist, int nsamples, int nbins)
{
    // For uniform distribution, expected is same for all bins.
    double expected = nsamples/nbins;
    double sum = 0;
    for (int i = 0; i < nbins; ++i) {
        auto obs_minus_expected = hist[i]-expected;
        sum += (obs_minus_expected*obs_minus_expected);
    }
    return sum/expected;
}

TEST_CASE("[uniform_int_distribution]")
{
    int minv = 1, maxv = 6;
    std::random_device seed;
    std::default_random_engine gen{seed()};
    std::uniform_int_distribution<int> dis(minv, maxv); // Closed interval: [minv,maxv]

    int nbins = maxv-minv+1;
    std::vector<int> hist(nbins, 0);
    int nsamples = 12'000;
    for (int ntrial = 0; ntrial < nsamples; ++ntrial) {
        auto binv = dis(gen) - minv; // binv starts from bin 0.
        ++hist[binv];
    }

    for (int i = minv; i <= maxv; ++i) {
        std::cout << "[" << i << "]=" << hist[i-minv] << "\n";
    }

    // https://www.itl.nist.gov/div898/handbook/eda/section3/eda3674.htm
    // Critical value for alpha=0.99, k-1=nbins-1=5 is 15.086
    double chisqv = chisq_vec(hist, nsamples, nbins);
    double critv = 15.086;
    INFO("chisq:", chisqv);
    INFO("critv:", critv);
    REQUIRE(chisqv < critv);
}

double chisq_map(const std::map<double, int>& hist, int nsamples, int nbins)
{
    // For uniform distribution, expected is same for all bins.
    double expected = nsamples/nbins;
    double sum = 0;
    for (const auto& bin : hist) {
        auto obs_minus_expected = bin.second-expected;
        sum += (obs_minus_expected*obs_minus_expected);
    }
    return sum/expected;
}

TEST_CASE("[uniform_real_distribution]")
{
    double minv = 0., maxv = 1.;
    std::random_device seed;
    std::default_random_engine gen{seed()};
    std::uniform_real_distribution<double> dis(minv, maxv); // Open interval: [minv,maxv)

    int nbins = 10;
    std::map<double, int> hist; // Left edges.
    int nsamples = 12'000;
    for (int ntrial = 0; ntrial < nsamples; ++ntrial) {
        auto binv = int(dis(gen)*nbins)/double(nbins); // f.p. to bin
        ++hist[binv];
    }

    for (const auto& bin : hist) {
        std::cout << "[" << bin.first << "]=" << bin.second << "\n";
    }

    // https://www.itl.nist.gov/div898/handbook/eda/section3/eda3674.htm
    // Critical value for alpha=0.99, k-1=nbins-1=9 is 21.666
    double chisqv = chisq_map(hist, nsamples, nbins);
    double critv = 21.666;
    INFO("chisq:", chisqv);
    INFO("critv:", critv);
    REQUIRE(chisqv < critv);
}
