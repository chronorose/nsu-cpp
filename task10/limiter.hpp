#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T, size_t Limit>
class Limiter {
  inline static size_t objs = 0;
  // honestly, why does it work with inline and doesn't without it? it's
  // pretty cursed if you think about it. like, how does inline matter
  // there???

  void ctr() {
    if (objs >= Limit) {
      throw std::logic_error("oopsie daisy");
    }
    ++objs;
  }

public:
  Limiter() { ctr(); }

  Limiter(const Limiter& other) { ctr(); }

  ~Limiter() { --objs; }
};
