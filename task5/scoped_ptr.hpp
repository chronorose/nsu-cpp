#pragma once

#include <concepts>
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
  T* operator->() { return ptr; }
  T& operator*() { return get(); }
  const T& get() const { return *ptr; }
  ~UniqueScopedPtr() { delete ptr; }
};

template <std::copy_constructible T>
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
  DCScopedPtr(DCScopedPtr&& other) { std::swap(ptr, other.ptr); }
  DCScopedPtr& operator=(DCScopedPtr&& other) {
    std::swap(ptr, other.ptr);
    return *this;
  }
  T& get() { return *ptr; }
  T* operator->() { return ptr; }
  T& operator*() { return get(); }
  const T& get() const { return *ptr; }
  ~DCScopedPtr() { delete ptr; }
};
