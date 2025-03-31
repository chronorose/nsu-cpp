#pragma once

#include <string>
#include <string_view>
#include <vector>

enum class LexemeType {
  LParen,
  RParen,
  Id,
  Int,
  Equals,
};

class LexerException {
public:
  std::string error_msg;
  LexerException(std::string error) : error_msg(error) {}
};

// could do some spans. couldn't care tho.
class Lexeme {
  LexemeType type_;
  std::string lexeme_;

public:
  Lexeme(LexemeType type, std::string& lexeme) : type_(type), lexeme_(lexeme) {}
  LexemeType type() const { return type_; }
  const std::string lexeme() const { return lexeme_; }
};

class ILexer {

public:
  virtual std::vector<Lexeme> lex(const std::string_view stringInput) = 0;
  virtual ~ILexer() {};
};
