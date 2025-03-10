#pragma once

#include <utility>
template <typename T>
class UniqueScopedPtr {
  T* ptr = nullptr;

public:
  UniqueScopedPtr(T* ptr) : ptr(ptr) {}
  UniqueScopedPtr(const UniqueScopedPtr& other) = delete;
  UniqueScopedPtr& operator=(const UniqueScopedPtr& other) = delete;
  UniqueScopedPtr(UniqueScopedPtr&& other) { std::swap(ptr, other.ptr); }
  UniqueScopedPtr& operator=(UniqueScopedPtr&& other) {
    std::swap(ptr, other.ptr);
    return *this;
  }
  T& get() { return *ptr; }
  const T& get() const { return *ptr; }
  ~UniqueScopedPtr() { delete ptr; }
};

// ideally we would need to check that T is deep-copyable here
template <typename T>
class DCScopedPtr {
  T* ptr = nullptr;

public:
  DCScopedPtr(T* ptr) : ptr(ptr) {}
  DCScopedPtr(const DCScopedPtr& other) { ptr = new T(*other.ptr); }
  DCScopedPtr& operator=(const DCScopedPtr& other) {
    if (this == &other)
      return *this;
    delete ptr;
    ptr = new T(*other.ptr);
    return *this;
  }
  // not really sure about move constructors...
  DCScopedPtr(DCScopedPtr&& other) { std::swap(ptr, other.ptr); }
  DCScopedPtr& operator=(DCScopedPtr&& other) {
    std::swap(ptr, other.ptr);
    return *this;
  }
  T& get() { return *ptr; }
  const T& get() const { return *ptr; }
  ~DCScopedPtr() { delete ptr; }
};
