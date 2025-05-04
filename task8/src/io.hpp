#pragma once

class IO {
protected:
  bool open = false;
  bool end_ = false;

public:
  virtual void close() = 0;
  virtual bool end() = 0;
};
