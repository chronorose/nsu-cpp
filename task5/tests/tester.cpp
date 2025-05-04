#include "../scoped_ptr.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

class DestructorTest {
  bool destructed_;

public:
  DestructorTest() : destructed_(false) {}
  DestructorTest(const DestructorTest& other) = default;
  void destruction() { destructed_ = !destructed_; }
  bool destructed() { return destructed_; }
};

struct TestObject {
  DestructorTest& dt;
  TestObject(DestructorTest& dt) : dt(dt) {}
  TestObject(const TestObject& other) = default;
  ~TestObject() { dt.destruction(); }
};

TEST(unique_scoped_ptr, leak_test) {
  DestructorTest dt;
  {
    TestObject* to = new TestObject(dt);
    UniqueScopedPtr<TestObject> usp(to);
  }
  EXPECT_TRUE(dt.destructed());
}

TEST(unique_scoped_ptr, no_doublefree_move_assignment) {
  DestructorTest dt;
  {
    TestObject* to = new TestObject(dt);
    UniqueScopedPtr<TestObject> usp(to);
    UniqueScopedPtr<TestObject> lol = std::move(usp);
  }
  EXPECT_TRUE(dt.destructed());
}

TEST(unique_scoped_ptr, no_doublefree_move_ctr) {
  DestructorTest dt;
  {
    TestObject* to = new TestObject(dt);
    UniqueScopedPtr<TestObject> usp(to);
    UniqueScopedPtr<TestObject> lol(std::move(usp));
  }
  EXPECT_TRUE(dt.destructed());
}

TEST(dc_scoped_ptr, leak_test) {
  DestructorTest dt;
  {
    TestObject* to = new TestObject(dt);
    DCScopedPtr<TestObject> usp(to);
  }
  EXPECT_TRUE(dt.destructed());
}

TEST(dc_scoped_ptr, no_double_free_move) {
  DestructorTest dt;
  {
    TestObject* to = new TestObject(dt);
    DCScopedPtr<TestObject> usp(to);
    DCScopedPtr<TestObject> usp2 = std::move(usp);
  }
  EXPECT_TRUE(dt.destructed());
}

// honestly cannot really come up with a good way
// to test copy constructors in any way
// i'll keep thinking about it
