#pragma once
#include <concepts>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <optional>
#include <ostream>
#include <utility>

using std::optional, std::pair, std::rand;

template <std::integral T, std::copyable U> class Treap {
  struct Node {
    T key;
    size_t prio;
    U elem;
    Node* left;
    Node* right;
    Node(T key, U elem) : key(key), elem(elem), left(nullptr), right(nullptr) {
      prio = rand();
    }
  };
  using NodeT = Node;
  using OptionU = optional<std::reference_wrapper<U>>;
  NodeT* root;

  pair<NodeT*, NodeT*> split(NodeT* t, T k) {
    if (t == nullptr)
      return {nullptr, nullptr};
    if (k <= t->key) {
      auto [ll, lr] = split(t->left, k);
      t->left = lr;
      return {ll, t};
    }
    auto [rl, rr] = split(t->right, k);
    t->right = rl;
    return {t, rr};
  }

  NodeT* merge(NodeT* t1, NodeT* t2) {
    if (t1 == nullptr)
      return t2;
    if (t2 == nullptr)
      return t1;

    if (t1->prio > t2->prio) {
      t1->right = merge(t1->right, t2);
      return t1;
    }

    t2->left = merge(t1, t2->left);
    return t2;
  }

  void rec_delete(NodeT* node) {
    if (node == nullptr)
      return;
    rec_delete(node->left);
    rec_delete(node->right);
    delete node;
  }

public:
  Treap() { root = nullptr; }

  // i understand that returning optional<U>
  // is probably not the correct choice.
  // however i do not want to have reference_wrap
  // nightmare again, so i guess it shall be so.
  optional<U> search(T key) {
    auto [lt, mt] = split(root, key);
    auto [_, rt] = split(mt, key + 1);
    if (mt && mt->key == key) {
      T elem = mt->elem;
      root = merge(merge(lt, mt), rt);
      return optional{elem};
    }
    root = merge(merge(lt, mt), rt);
    return {};
  }
  void insert(U elem, T key) {
    auto [t1, t2] = split(root, key);
    NodeT* new_node = new NodeT(key, elem);
    root = merge(merge(t1, new_node), t2);
  }
  optional<U> remove(T key) {
    auto [lt, mt] = split(root, key);
    auto [_, rt] = split(mt, key + 1);
    root = merge(lt, rt);
    if (mt && mt->key == key) {
      T elem = mt->elem;
      delete mt;
      return optional{elem};
    }
    return {};
  }

  ~Treap() { rec_delete(root); }
};
