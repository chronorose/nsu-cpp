#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

/* Note: about using namespaces in header files
 * we don't discuss namespaces on lectures, so it is just advice
 * - avoid of usage 'using' in headers. User, that includes your header
 * may already have 'string' or 'unordered_map' in his global namespace.
 * So include your header file will cause name clash and compilation error
 */
using std::cout, std::endl;
using std::unordered_map, std::string;

template <class CharT>
class Trie {
  struct TrieNode {
    unordered_map<CharT, TrieNode*> map;
    bool leaf;
    TrieNode() : leaf(false) {}
  };
  TrieNode* root;

  void ins_(std::basic_string<CharT>& word, TrieNode* node, size_t current) {
    if (current >= word.size())
      return;
    auto is_terminal = (word.size() - 1) == current;
    auto current_symbol = word.at(current);
    TrieNode* new_node;
    // Note: yeah, me too feeling this functional pain..
    // why can't i return new_node from if T_T
    // give me my if expressions, not statements T_T
    if (!node->map.contains(current_symbol)) {
      new_node = new TrieNode();
      node->map.insert({current_symbol, new_node});
    } else {
      new_node = node->map[current_symbol];
    }
    new_node->leaf = new_node->leaf || is_terminal;
    ins_(word, new_node, current + 1);
  }

  bool search_(std::basic_string<CharT>& word, TrieNode* node, size_t current) {
    if (current >= word.length())
      return false;
    auto current_symbol = word.at(current);
    auto is_terminal = (word.size() - 1) == current;
    if (!node->map.contains(current_symbol))
      return false;
    auto new_node = node->map[current_symbol];
    if (is_terminal)
      return new_node->leaf;
    return search_(word, new_node, current + 1);
  }

  /* RE: about copying of acc 
   * Acc is nice, but each recursive call will you use copy constructor of std::string
   * Maybe we can initialize acc once, and then passing reference to it?
   *
   * RE: about compilation
   * sometimes this methods gives us compilation errors
   */
  void rec_print(TrieNode* node, string acc) {
    for (auto& it : node->map) {
      rec_print(it.second, acc + it.first);
    }
    if (node->leaf) {
      std::cout << acc << std::endl;
    }
  }

  void rec_delete(TrieNode* node) {
    for (auto& it : node->map) {
      rec_delete(it.second);
    }
    delete node;
  }

  /* RE: About correctness
   * This methods produces TrieNodes with broken invariants
   */
  TrieNode* rec_copy(TrieNode* node) {
    auto new_node = new TrieNode();
    for (auto& it : node->map) {
      auto copy_node = rec_copy(it.second);
      new_node->map.insert({it.first, copy_node});
    }
    return new_node;
  }

public:
  Trie() : root(new TrieNode()) {}
  Trie(const Trie& other) : root(rec_copy(other.root)) {}
  Trie& operator=(const Trie& other) {
    if (this == &other)
      return *this;
    rec_delete(root);
    root = rec_copy(other.root);
  }
  void insert(std::basic_string<CharT>& word) { ins_(word, root, 0); }
  bool search(std::basic_string<CharT>& word) { return search_(word, root, 0); }
  void print() { rec_print(root, ""); }
  ~Trie() { rec_delete(root); }
};
