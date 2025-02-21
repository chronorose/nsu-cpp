#include "../trie.hpp"
#include "gtest/gtest.h"
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

TEST(trie, trie_basic_test) {
  auto trie = Trie<char>();
  string str = "Hello";
  trie.insert(str);
  EXPECT_TRUE(trie.search(str));
}

TEST(trie, trie_mass_insert_search) {
  auto trie = Trie<char>();
  vector<string> vec = {"hello",      "hi",      "very cool", "amazing",
                        "finally",    "case",    "switch",    "switching",
                        "switcharoo", "coolity", "very fun"};
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_mass_insert_search2) {
  auto trie = Trie<char>();
  vector<string> vec = {"hello",
                        "hi",
                        "very cool",
                        "amazing",
                        "finally",
                        "case",
                        "switch",
                        "switching",
                        "switcharoo",
                        "coolity",
                        "very fun",
                        "switch",
                        "switch",
                        "very cool",
                        "foolish",
                        "i am your father luke",
                        "hello there",
                        "i have a bad feeling about this",
                        "I JUST NOTICED THERE ARE NO TESTS THAT SCREAM",
                        "NOW IT IS DIFFERENT"};
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

template <class CharT>
basic_string<CharT> gen_random_string() {
  size_t len = rand() % 10000;
  basic_string<CharT> random_string;
  random_string.reserve(len);
  for (size_t i = 0; i < len; i++) {
    random_string.push_back(rand());
  }
  return random_string;
}

TEST(trie, trie_sort_of_fuzz) {
  srand(time({}));
  auto trie = Trie<char>();
  vector<string> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    vec.push_back(gen_random_string<char>());
  }
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_sort_of_fuzz2) {
  srand(time({}));
  auto trie = Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    vec.push_back(gen_random_string<char32_t>());
  }
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}
