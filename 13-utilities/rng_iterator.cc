// An iterator that returns an infinite sequence of random integers.
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// rng_iterator returns a infinite sequence of random integers.
class rng_iterator
{
  public:
    class iterator
    {
      public:
        // Inheriting from std::iterator deprecated in C++17.
        // Instead explicitly add the iterator trait typedefs.
        using iterator_category = std::input_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int*;
        using reference = int;

        iterator(rng_iterator& rng) : rng(rng) { }

        // operator++ generates the next pseudorandom value in the sequence.
        iterator& operator++()
        {
            value = rng.dis(rng.gen);
            return *this;
        }

        // operator++ generates the next pseudorandom value in the sequence.
        iterator operator++(int)
        {
            iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(const iterator& other) const
        {
            return (this == &other) ? true : false; // Equality means identity.
        }

        bool operator !=(const iterator& other) const
        {
            return !(*this == other);
        }

        reference operator*() const
        {
            return value;
        }

      private:
        rng_iterator& rng;
        int value{0};
    };

    // rng_iterator iterators return values in closed interval: [minv, maxv].
    rng_iterator(int minv=1, int maxv=6) : gen(seed()), dis(minv, maxv) { }

    // begin() satisfies requirements for range-based for loop.
    iterator begin()
    {
        return iterator(*this);
    }

    // end() returns a new iterator that is never equal to begin().
    iterator end()
    {
        return iterator(*this);
    }

  private:
    // Iterators produced from the this instance share the same generator.
    std::random_device seed;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dis;
};

double chisq_vec(const int* hist, int nsamples, int nbins)
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

TEST_CASE("[rng_iterator]")
{
    int minv = 1, maxv = 6; // d6.
    rng_iterator rng(minv, maxv);

    int nbins = maxv - minv + 1;
    std::vector<int> hist(minv + nbins, 0);
    int nsamples = 12'000, ntrial = 0;
    for (const auto& v : rng) {
        ++hist[v];
        if (++ntrial == nsamples) {
            break;
        }
    }

    for (int i = minv; i <= maxv; ++i) {
        std::cout << "[" << i << "]=" << hist[i] << "\n";
    }

    // https://www.itl.nist.gov/div898/handbook/eda/section3/eda3674.htm
    // Critical value for alpha=0.99, k-1=nbins-1=5 is 15.086
    double chisqv = chisq_vec(&hist[minv], nsamples, nbins);
    double critv = 15.086;
    INFO("chisq:", chisqv);
    INFO("critv:", critv);
    REQUIRE(chisqv < critv);
}

TEST_CASE("[rng_iterator::operator==]")
{
    rng_iterator rng;
    {
        auto it = rng.begin();
        auto it2 = it; // Copy does not share identity.
        REQUIRE(it != it2);
    }
    {
        auto it = rng.begin();
        auto& it2 = it; // Reference shares identity.
        REQUIRE(it == it2);
    }
}
