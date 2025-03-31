#include "../src/exec/lang.hpp"
#include "../src/lexer/lexer.hpp"
#include "../src/parser/parser.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ostream>

using namespace std;

int getValFromStr(std::string str) {
  auto lexer = LexerImpl();
  auto parser = ParserImpl();
  auto lexed = lexer.lex(str);
  auto parsed = parser.parse(lexed);
  auto env = Env();
  auto evaled = parsed->eval(env)->get_val();
  return evaled;
}

TEST(execTest, first_test) {
  auto inputStr = "(let K = (val 10) in (add (val 5) (var K)))";
  auto expected = 15;
  auto res = getValFromStr(inputStr);
  ASSERT_EQ(expected, res);
}

TEST(execTest, second_test) {
  auto inputStr = "(let A = (val 20)"
                  "in (let B = (val 30)"
                  "in (if (var A) (add (var B)"
                  "(val 3)) then (val 10) else (add (var B) (val 1)))))";
  auto expected = 31;
  auto res = getValFromStr(inputStr);
  ASSERT_EQ(expected, res);
}

TEST(execTest, third_test) {
  auto inputStr = "(let F ="
                  "(function arg"
                  "(add (var arg) (val 1))) in"
                  "(let V = (val 1) in (call (var F) (var V))))";
  auto expected = 2;
  auto res = getValFromStr(inputStr);
  ASSERT_EQ(expected, res);
}
