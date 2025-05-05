#include "../limiter.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

class HelloKitty : Limiter<HelloKitty, 1> {};

class TwoMeows : Limiter<TwoMeows, 2> {};

class ThreeKitties : Limiter<ThreeKitties, 3> {};

TEST(limiter, test1) {
  auto meow = HelloKitty();
  ASSERT_THROW(HelloKitty(), logic_error);
}

TEST(limiter, boundedNumberOfCopiedCats) {
  HelloKitty original_cat;
  ASSERT_THROW(HelloKitty copied_cat{original_cat}, logic_error);
}

TEST(limiter, test2) {
  TwoMeows* tm = new TwoMeows{};
  TwoMeows* tm2 = new TwoMeows{};
  delete tm;
  tm = new TwoMeows{};
  ASSERT_THROW(TwoMeows(), logic_error);
}

TEST(limiter, test3) { ASSERT_THROW(ThreeKitties tk[4], logic_error); }
