#pragma once

#include "io.hpp"
#include <string>

class Reader : virtual public IO {
public:
  virtual Reader& operator>>(std::string&) = 0;
  virtual Reader& operator>>(int&) = 0;
  virtual Reader& operator>>(char&) = 0;
};
