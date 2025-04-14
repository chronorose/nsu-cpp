#pragma once

#include <cctype>
#include <string>

#include "io.hpp"
#include "reader.hpp"
#include "readerwriter.hpp"
#include "writer.hpp"

class StringIO : virtual public IO {
protected:
  std::string input;
  size_t pos = 0;

public:
  StringIO(std::string input) : input(input) { open = true; }
  virtual void close() override { open = false; }
  virtual bool end() override { return pos >= input.size(); }
};

class StringReader : virtual public StringIO, virtual public Reader {

public:
  StringReader(std::string input) : StringIO(input) {}
  virtual StringReader& operator>>(std::string& str) {
    if (!open)
      return *this;
    while (!end() && std::isspace(input[pos]))
      ++pos;
    while (!end() && !std::isspace(input[pos])) {
      str.push_back(input[pos++]);
    }
    return *this;
  }

  virtual StringReader& operator>>(char& ch) {
    if (!open)
      return *this;
    while (!end() && !std::isalnum(input[pos]))
      ++pos;
    if (!end() && std::isalnum(input[pos]))
      ch = input[pos++];
    return *this;
  }

  virtual StringReader& operator>>(int& i) {
    if (!open)
      return *this;
    std::string holder;
    while (!end() && !std::isdigit(input[pos]))
      ++pos;
    while (!end() && std::isdigit(input[pos])) {
      holder += input[pos++];
    }
    i = std::stoi(holder);
    return *this;
  }
};

class StringWriter : virtual public StringIO, virtual public Writer {

public:
  StringWriter(std::string input) : StringIO(input) {}

  virtual Writer& operator<<(std::string& str) {
    if (!open)
      return *this;
    for (auto&& s : str) {
      input.push_back(s);
    }
    return *this;
  }
};

class StringRW : virtual public StringReader,
                 virtual public StringWriter,
                 virtual public ReaderWriter {};
