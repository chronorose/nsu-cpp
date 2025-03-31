#pragma once

#include <memory>
#include <string>

class Expr {
public:
  // yeah i know it's not idiomatic.
  virtual std::string toString() = 0;
  virtual ~Expr() {};
};

class Val : public Expr {
  int value;

public:
  Val(int value) : value(value) {}
  virtual std::string toString() {
    return "(val " + std::to_string(value) + ")";
  }
};

class Var : public Expr {
  std::string id;

public:
  Var(std::string id) : id(id) {}
  virtual std::string toString() { return "(var " + id + ")"; }
};

class Add : public Expr {
  std::shared_ptr<Expr> lhs;
  std::shared_ptr<Expr> rhs;

public:
  Add(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs)
      : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() {
    return "(add " + lhs->toString() + " " + rhs->toString() + ")";
  }
};

class If : public Expr {
  std::shared_ptr<Expr> lhs;
  std::shared_ptr<Expr> rhs;
  std::shared_ptr<Expr> tbranch;
  std::shared_ptr<Expr> fbranch;

public:
  If(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs,
     std::shared_ptr<Expr> tbranch, std::shared_ptr<Expr> fbranch)
      : lhs(lhs), rhs(rhs), tbranch(tbranch), fbranch(fbranch) {}
  virtual std::string toString() {
    return "(if " + lhs->toString() + " > " + rhs->toString() + " " +
           tbranch->toString() + " " + fbranch->toString() + ")";
  }
};

class Let : public Expr {
  std::string id;
  std::shared_ptr<Expr> given;
  std::shared_ptr<Expr> expression;

public:
  Let(std::string id, std::shared_ptr<Expr> given,
      std::shared_ptr<Expr> expression)
      : id(id), given(given), expression(expression) {}

  virtual std::string toString() {
    return "(let " + id + " " + given->toString() + " in " +
           expression->toString() + ")";
  }
};

class Function : public Expr {
  std::string id;
  std::shared_ptr<Expr> body;

public:
  Function(std::string id, std::shared_ptr<Expr> body) : id(id), body(body) {}
  virtual std::string toString() {
    return "(define " + id + " " + body->toString() + ")";
  }
};

class Call : public Expr {
  std::shared_ptr<Expr> fn;
  std::shared_ptr<Expr> arg;

public:
  Call(std::shared_ptr<Expr> fn, std::shared_ptr<Expr> arg)
      : fn(fn), arg(arg) {}
  virtual std::string toString() {
    return "(call " + fn->toString() + " " + arg->toString() + ")";
  }
};
