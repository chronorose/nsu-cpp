#include "lexer.hpp"
#include "ilexer.hpp"
#include <string>
#include <string_view>
#include <vector>

using view = std::string_view;
using buffer = std::vector<Lexeme>;
using iter = view::const_iterator;

static void skipWhitespace(iter& input, iter& end) {
  while ((input != end) && isspace(*input))
    ++input;
}

// we assume that input is in position where first symbol is, in fact, number.
static Lexeme lexInt(iter& input, iter& inputEnd) {
  std::string num;
  for (; input != inputEnd; ++input) {
    auto ch = *input;
    if (!isdigit(ch))
      break;
    num.push_back(ch);
  }
  return Lexeme(LexemeType::Int, num);
}

static Lexeme lexId(iter& input, iter& inputEnd) {
  std::string id;
  for (; input != inputEnd; ++input) {
    auto ch = *input;
    if ((!isalnum(ch)) && (ch != '_') && (ch != '-'))
      break;
    id.push_back(ch);
  }
  return Lexeme(LexemeType::Id, id);
}

// it takes input and returns iter to the first element
// after the lexeme
static Lexeme lex(iter& input, iter& inputEnd) {
  auto ch = *input;
  switch (ch) {
  case '(': {
    auto lexemeStr = std::string{ch};
    ++input;
    return Lexeme(LexemeType::LParen, lexemeStr);
  } break;
  case '=': {
    auto lexemeStr = std::string{ch};
    ++input;
    return Lexeme(LexemeType::Equals, lexemeStr);
  } break;

  case ')': {
    auto lexemeStr = std::string{ch};
    ++input;
    return Lexeme(LexemeType::RParen, lexemeStr);
  } break;
  default:
    if (isdigit(ch) || ch == '-') {
      return lexInt(input, inputEnd);
    }
    if (isalpha(ch)) {
      return lexId(input, inputEnd);
    }
    throw LexerException("Symbol is not lexable, gg " + std::to_string(ch));
  }
}

static void lexStr(iter& input, iter& end, buffer& buffer) {
  skipWhitespace(input, end);
  for (; input != end;) {
    buffer.push_back(lex(input, end));
    skipWhitespace(input, end);
  }
}

std::vector<Lexeme> LexerImpl::lex(const view stringInput) {
  iter iterator = stringInput.cbegin();
  iter iend = stringInput.cend();
  std::vector<Lexeme> retVec{};
  lexStr(iterator, iend, retVec);
  return retVec;
}
