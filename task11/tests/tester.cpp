#include "../primer.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

TEST(primes, first) { ASSERT_EQ(Prime<0>{}, 2); }
TEST(primes, second) { ASSERT_EQ(Prime<1>{}, 3); }
TEST(primes, third) { ASSERT_EQ(Prime<2>{}, 5); }
TEST(primes, fifth) { ASSERT_EQ(Prime<5>{}, 13); }
