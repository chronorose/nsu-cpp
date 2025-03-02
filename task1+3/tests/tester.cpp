#include "../trie.hpp"
#include "gtest/gtest.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

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
template <class CharT>
basic_string<CharT> gen_random_string() {
  std::uniform_int_distribution<size_t> len_dist(0, 10000); // this things needed to keep uniformity of distr
  std::uniform_int_distribution<char> chr_dist(0, 127);
  size_t len = len_dist(gen);
  basic_string<CharT> random_string;
  random_string.reserve(len);
  for (size_t i = 0; i < len; i++) {
    random_string.push_back(chr_dist(gen)); // Note: this is pointless and UB in previous version 
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

  trie.print();
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

/* RE: This test doesn't tests anything */
TEST(trie, trie_copy_constr) {
  srand(time({}));
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    vec.push_back(gen_random_string<char32_t>());
  }
  auto trie(*new_trie); // RE: yeah, there is no memory leaks, and it is nice
  delete new_trie;      // but if new_trie is empty, see the next test
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_copy_constr_review) {
  srand(time({}));
  auto new_trie = new Trie<char>();
  vector<std::string> vec = {"hello", "he-he", "hell"};
  const size_t str_amount = vec.size();

  for (auto& word : vec) {
      new_trie->insert(word);
  }

  for (auto& word : vec) {
    EXPECT_TRUE(new_trie->search(word));
  }

  auto trie(*new_trie);

  delete new_trie;

  // RE: if new_trie is nonempty,
  // then copyied trie will be invalidated
  for (auto& it : vec) {
    std::cout << it << std::endl;
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
    vec.push_back(gen_random_string<char32_t>());
  }

  auto trie(*new_trie);
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

/* RE: same as above
 */
TEST(trie, trie_copy_assignment) {
  srand(time({}));
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    vec.push_back(gen_random_string<char32_t>());
  }
  auto trie = *new_trie;
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

/* RE: same as above
 */
TEST(trie, trie_copy_assignment2) {
  srand(time({}));
  auto new_trie = new Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    vec.push_back(gen_random_string<char32_t>());
  }
  auto trie = *new_trie;
  delete new_trie;
  for (auto& it : vec) {
    trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(trie.search(it));
  }
}

TEST(trie, trie_copy_assignment_same) {
  srand(time({}));
  auto new_trie = Trie<char32_t>();
  vector<basic_string<char32_t>> vec;
  const size_t str_amount = 20;
  for (size_t i = 0; i < str_amount; i++) {
    vec.push_back(gen_random_string<char32_t>());
  }
  new_trie = new_trie;
  for (auto& it : vec) {
    new_trie.insert(it);
  }
  for (auto& it : vec) {
    EXPECT_TRUE(new_trie.search(it));
  }
}
