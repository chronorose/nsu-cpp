#include "../trie.hpp"
#include "gtest/gtest.h"
#include <cstdlib>
#include <ctime>
#include <random>
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

static std::random_device rd;  // this is thing that uses true randmoness
                               // we use it to produce seeds
static std::mt19937 gen(rd()); // this is 'generator' of pseudo-random numbers

/* Note:
 * for now this function a little bit pointless
 * we need to use type trait concept to write it in right way
 */
template <Trieable CharT>
basic_string<CharT> gen_random_string() {
  std::uniform_int_distribution<size_t> len_dist(
      0, 10000); // this things needed to keep uniformity of distr
  std::uniform_int_distribution<char> chr_dist(0, 127);
  size_t len = len_dist(gen);
  basic_string<CharT> random_string;
  random_string.reserve(len);
  for (size_t i = 0; i < len; i++) {
    random_string.push_back(
        chr_dist(gen)); // Note: this is pointless and UB in previous version
  }
  return random_string;
}

TEST(trie, trie_sort_of_fuzz) {
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

TEST(trie, trie_copy_constr) {
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    auto str = gen_random_string<char32_t>();
    vec.push_back(str);
    new_trie->insert(str);
  }
  auto trie(*new_trie);
  delete new_trie;
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_copy_constr_review) {
  auto new_trie = new Trie<char>();
  vector<std::string> vec = {"hello", "he-he", "hell"};

  for (auto& word : vec) {
    new_trie->insert(word);
  }

  for (auto& word : vec) {
    EXPECT_TRUE(new_trie->search(word));
  }

  auto trie(*new_trie);

  delete new_trie;

  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

/* RE: almost useless test
 * So please check data consitency
 */
TEST(trie, trie_copy_constr2) {
  srand(time({}));
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;

  for (size_t i = 0; i < str_amount; i++) {
    auto str = gen_random_string<char32_t>();
    vec.push_back(str);
    new_trie->insert(str);
  }

  auto trie(*new_trie);

  for (size_t i = 0; i < str_amount; i++) {
    auto str = gen_random_string<char32_t>();
    vec.push_back(str);
    trie.insert(str);
  }
  const size_t upper_bound = str_amount * 2;
  for (size_t i = str_amount; i < upper_bound; ++i) {
    EXPECT_FALSE(new_trie->search(vec.at(i)));
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_copy_assignment) {
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    auto str = gen_random_string<char32_t>();
    vec.push_back(str);
    new_trie->insert(str);
  }
  auto trie = *new_trie;
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
  delete new_trie;
}

/* RE: same as above
 */
TEST(trie, trie_copy_assignment2) {
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    auto str = gen_random_string<char32_t>();
    vec.push_back(str);
    new_trie->insert(str);
  }
  auto trie = *new_trie;
  delete new_trie;
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_copy_assignment_same) {
  auto new_trie = Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    auto str = gen_random_string<char32_t>();
    vec.push_back(str);
    new_trie.insert(str);
  }
  new_trie = new_trie;
  for (auto& it : vec) {
    EXPECT_TRUE(new_trie.search(it));
  }
}
