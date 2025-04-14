#pragma once

#include "io.hpp"
#include <string>

class Writer : virtual public IO {
public:
  virtual Writer& operator<<(std::string&) = 0;
};
