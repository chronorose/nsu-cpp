#include "../src/file.hpp"
#include "../src/string.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gtest/gtest.h>
#include <ostream>
#include <string>

using namespace std;

TEST(strings, inttest) {
  string hi = "   7891";
  StringReader sr{hi};
  int i;
  sr >> i;
  ASSERT_EQ(i, 7891);
}

TEST(strings, inttest2) {
  string hi = "   qweasd 7891"; // so i know it is questionable that it works
                                // like this. but it is intended. i
                                // think it is the way i would like it to work
                                // tbh, even if it is very questionable.
  StringReader sr{hi};
  int i;
  sr >> i;
  ASSERT_EQ(i, 7891);
}

TEST(strings, inttest3) {
  string hi = "   7 7891";
  StringReader sr{hi};
  int i;
  sr >> i;
  ASSERT_EQ(i, 7);
}

TEST(strings, chartest1) {
  string hi = "   7 7891";
  StringReader sr{hi};
  char i;
  sr >> i;
  ASSERT_EQ(i, '7');
}

TEST(strings, stringtest) {
  string hi = "  7123 7891";
  StringReader sr{hi};
  string i;
  sr >> i;
  ASSERT_EQ(i, "7123");
}

TEST(files, stringtest1) {
  string hi = "../tests/inputs/test1.txt";
  FileReader sr{hi};
  string i;
  sr >> i;
  ASSERT_EQ(i, "hello!!");
}

TEST(files, inttest1) {
  string hi = "../tests/inputs/test2.txt";
  FileReader sr{hi};
  int i;
  sr >> i;
  ASSERT_EQ(i, 228);
}

TEST(files, chartest1) {
  string hi = "../tests/inputs/test1.txt";
  FileReader sr{hi};
  char i;
  sr >> i;
  ASSERT_EQ(i, 'h');
}
