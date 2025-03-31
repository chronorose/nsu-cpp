#include "parser.hpp"
#include "iparser.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

using buffer = std::vector<Lexeme>;
using iter = buffer::const_iterator;
using spExpr = std::shared_ptr<Expr>;
using parseFn = std::function<spExpr(iter&, iter&)>;
using umap = std::unordered_map<std::string, parseFn>;
static spExpr expr(iter& start, iter& end);

static void expect(LexemeType expected, Lexeme& actual) {
  if (expected != actual.type())
    throw ParserException("expect failed, expected" +
                          std::to_string((int)expected) +
                          ", actual: " + actual.lexeme());
}

static void expectId(Lexeme& actual, std::string expected) {
  if (actual.type() != LexemeType::Id || actual.lexeme() != expected) {
    throw ParserException("expected id " + expected);
  }
}

static void expectLeftParen(Lexeme& lexeme) {
  expect(LexemeType::LParen, lexeme);
}

static void expectRightParen(Lexeme& lexeme) {
  expect(LexemeType::RParen, lexeme);
}

static void inc(iter& start, iter& end) {
  ++start;
  if (start == end)
    throw ParserException("end is too soon");
}

spExpr parseAdd(iter& cur, iter& end) {
  auto lhs = expr(cur, end);
  inc(cur, end);
  auto rhs = expr(cur, end);
  inc(cur, end);
  return std::make_shared<Add>(lhs, rhs);
}

spExpr parseIf(iter& cur, iter& end) {
  auto lhs = expr(cur, end);
  inc(cur, end);

  auto rhs = expr(cur, end);
  inc(cur, end);

  auto thenToken = *cur;
  expectId(thenToken, "then");
  inc(cur, end);

  auto tbranch = expr(cur, end);
  inc(cur, end);

  auto elseToken = *cur;
  expectId(elseToken, "else");
  inc(cur, end);

  auto fbranch = expr(cur, end);
  inc(cur, end);
  return std::make_shared<If>(lhs, rhs, tbranch, fbranch);
}

spExpr parseLet(iter& cur, iter& end) {
  auto id = *cur;
  expect(LexemeType::Id, id);
  inc(cur, end);

  auto equals = *cur;
  expect(LexemeType::Equals, equals);
  inc(cur, end);

  auto given = expr(cur, end);
  inc(cur, end);

  auto inToken = *cur;
  expectId(inToken, "in");
  inc(cur, end);

  auto expression = expr(cur, end);
  inc(cur, end);

  return std::make_shared<Let>(id.lexeme(), given, expression);
}

spExpr parseVal(iter& cur, iter& end) {
  auto num = *cur;
  expect(LexemeType::Int, num);
  inc(cur, end);
  return std::make_shared<Val>(std::stoi(num.lexeme()));
}

spExpr parseVar(iter& cur, iter& end) {
  auto id = *cur;
  expect(LexemeType::Id, id);
  inc(cur, end);
  return std::make_shared<Var>(id.lexeme());
}

spExpr parseFunc(iter& cur, iter& end) {
  auto id = *cur;
  expect(LexemeType::Id, id);
  inc(cur, end);

  auto expression = expr(cur, end);
  inc(cur, end);
  return std::make_shared<Function>(id.lexeme(), expression);
}

spExpr parseCall(iter& cur, iter& end) {
  auto fn = expr(cur, end);
  inc(cur, end);

  auto arg = expr(cur, end);
  inc(cur, end);
  return std::make_shared<Call>(fn, arg);
}

umap keywords = {
    {"add", parseAdd},   {"val", parseVal}, {"var", parseVar},
    {"if", parseIf},     {"let", parseLet}, {"function", parseFunc},
    {"call", parseCall},

};

static spExpr expr(iter& start, iter& end) {
  auto cur = *start;
  expectLeftParen(cur);
  inc(start, end);
  cur = *start;
  expect(LexemeType::Id, cur);
  if (!keywords.contains(cur.lexeme())) {
    throw ParserException("incorrect keyword");
  }
  inc(start, end);
  auto expr = keywords[cur.lexeme()](start, end);

  cur = *start;
  expectRightParen(cur);
  return expr;
}

std::shared_ptr<Expr> ParserImpl::parse(std::vector<Lexeme>& lexems) {
  auto begin = lexems.cbegin();
  auto end = lexems.cend();
  auto expression = expr(begin, end);
  return expression;
}
