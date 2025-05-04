#pragma once

#include <cctype>
#include <cstdio>
#include <string>

#include "io.hpp"
#include "reader.hpp"
#include "readerwriter.hpp"
#include "writer.hpp"

class FileIO : virtual public IO {
protected:
  FILE* input;

public:
  void close() override { open = false; }
  bool end() override { return feof(input); }
};

class FileReader : virtual public FileIO, virtual public Reader {
public:
  FileReader(std::string path) {
    input = fopen(path.c_str(), "r");
    open = true;
  }

  FileReader& operator>>(std::string& str) override {
    if (!open)
      return *this;
    char cholder = fgetc(input);
    while (!end() && std::isspace(cholder))
      cholder = fgetc(input);
    while (!end() && !std::isspace(cholder)) {
      str.push_back(cholder);
      cholder = fgetc(input);
    }
    return *this;
  }

  FileReader& operator>>(char& ch) override {
    if (!open)
      return *this;
    char holder = fgetc(input);
    while (!end() && !std::isalnum(holder))
      holder = fgetc(input);
    if (!end() && std::isalnum(holder))
      ch = holder;
    return *this;
  }

  FileReader& operator>>(int& i) override {
    if (!open)
      return *this;
    std::string holder;
    char cholder = fgetc(input);
    while (!end() && !std::isdigit(cholder))
      cholder = fgetc(input);
    while (!end() && std::isdigit(cholder)) {
      holder += cholder;
      cholder = fgetc(input);
    }
    i = std::stoi(holder);
    return *this;
  }
};

class FileWriter : virtual public FileIO, virtual public Writer {
public:
  FileWriter(std::string path) {
    input = fopen(path.c_str(), "w");
    open = true;
  }
  Writer& operator<<(std::string& str) {
    if (!open)
      return *this;

    auto size = str.size();

    fwrite(str.c_str(), size, size, input);

    return *this;
  }

  Writer& operator<<(int& integer) {
    if (!open)
      return *this;

    auto str = std::to_string(integer);

    auto size = str.size();

    fwrite(str.c_str(), size, size, input);

    return *this;
  }

  Writer& operator<<(char& ch) {
    if (!open)
      return *this;

    fputc(ch, input);

    return *this;
  }
};

class FileRW : virtual public FileReader,
               virtual public FileWriter,
               virtual public ReaderWriter {
public:
  FileRW(std::string path) {
    input = fopen(path.c_str(), "w+");
    open = true;
  }
};
