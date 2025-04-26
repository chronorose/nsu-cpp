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

class GiveMeMoreKitties : Limiter<GiveMeMoreKitties, 2> {};

TEST(limiter, test1) {
  auto meow = HelloKitty();
  ASSERT_THROW(HelloKitty(), logic_error);
}

TEST(limiter, test2) {
  TwoMeows* tm = new TwoMeows{};
  TwoMeows* tm2 = new TwoMeows{};
  delete tm;
  tm = new TwoMeows{};
  ASSERT_THROW(TwoMeows(), logic_error);
}

TEST(limiter, test3) { ASSERT_THROW(ThreeKitties tk[4], logic_error); }

/** Re: we can produce unbounded number of class instances using copy constructor
 *
 * To fix this, think about which base class constructor will be called 
 * before calling the copy constructor of the derived class.
 *
 * Note: We can also count the usage of the move constructor, 
 * but I think it's pointless. With its normal use, one object will be created, 
 * and one will be dead very soon.
 */
TEST(limiter, unboundedNumberOfCats) {
  GiveMeMoreKitties original_cat;
  GiveMeMoreKitties copied_cat {original_cat};

  ASSERT_THROW(GiveMeMoreKitties copy_of_copied_cat {}, logic_error);
}
