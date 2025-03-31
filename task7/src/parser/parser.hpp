#pragma once

#include "iparser.hpp"
#include <vector>
class ParserImpl : public IParser {

public:
  virtual std::shared_ptr<Expr> parse(std::vector<Lexeme>& lexemes);
};
