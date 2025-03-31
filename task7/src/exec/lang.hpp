#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Expr;

// i should inherit those from some std exception
class IdNotFoundException {
public:
  std::string error_msg;
  IdNotFoundException(std::string error) : error_msg(error) {}
};

class NotCallableCalled {
public:
  std::string error_msg;
  NotCallableCalled(std::string error) : error_msg(error) {}
};

class NotValue {
public:
  std::string error_msg;
  NotValue(std::string error) : error_msg(error) {}
};

class Env {
  std::unordered_map<std::string, std::shared_ptr<Expr>> env;

public:
  void addToEnv(std::string id, std::shared_ptr<Expr> expr) {
    env.insert({id, expr});
  }
  std::shared_ptr<Expr> getFromEnv(std::string id) const {
    if (!env.contains(id)) {
      throw IdNotFoundException("id " + id + " not found");
    }
    return env.at(id);
  }
};

class Expr {
public:
  // yeah i know it's not idiomatic.
  virtual std::string toString() = 0;
  std::shared_ptr<Expr> from_env(std::string id, const Env& env) {
    return env.getFromEnv(id);
  }
  virtual int get_val() { throw NotValue("tried to get_val() not from val"); }
  virtual std::shared_ptr<Expr> eval(Env env) = 0;
  virtual ~Expr() {};
};

class Val : public Expr {
  int value;

public:
  Val(int value) : value(value) {}
  virtual int get_val() { return value; }
  virtual std::shared_ptr<Expr> eval(Env env) {
    return std::make_shared<Val>(value);
  }
  virtual std::string toString() {
    return "(val " + std::to_string(value) + ")";
  }
};

class Var : public Expr {
  std::string id;

public:
  Var(std::string id) : id(id) {}
  virtual std::shared_ptr<Expr> eval(Env env) { return env.getFromEnv(id); }
  virtual std::string toString() { return "(var " + id + ")"; }
};

class Add : public Expr {
  std::shared_ptr<Expr> lhs;
  std::shared_ptr<Expr> rhs;

public:
  Add(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs)
      : lhs(lhs), rhs(rhs) {}
  virtual std::shared_ptr<Expr> eval(Env env) {
    auto vlhs = lhs->eval(env);
    auto vrhs = rhs->eval(env);
    return std::make_shared<Val>(vlhs->get_val() + vrhs->get_val());
  }
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
  virtual std::shared_ptr<Expr> eval(Env env) {
    auto vlhs = lhs->eval(env)->get_val();
    auto vrhs = rhs->eval(env)->get_val();
    if (vlhs > vrhs) {
      return tbranch->eval(env);
    }
    return fbranch->eval(env);
  }
};

class Let : public Expr {
  std::string id;
  std::shared_ptr<Expr> given;
  std::shared_ptr<Expr> expression;

public:
  virtual std::shared_ptr<Expr> eval(Env env) {
    env.addToEnv(id, given);
    return expression->eval(env);
  }
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
  std::string argId() { return id; }
  std::shared_ptr<Expr> fnBody() { return body; }
  virtual std::shared_ptr<Expr> eval(Env env) {
    return std::make_shared<Function>(id, body);
  }
  Function(std::string id, std::shared_ptr<Expr> body) : id(id), body(body) {}
  virtual std::string toString() {
    return "(define " + id + " " + body->toString() + ")";
  }
};

class Call : public Expr {
  std::shared_ptr<Expr> fn;
  std::shared_ptr<Expr> arg;

public:
  virtual std::shared_ptr<Expr> eval(Env env) {
    auto fnexpr = fn->eval(env);
    auto functionExpr = std::dynamic_pointer_cast<Function>(fnexpr);
    if (!functionExpr) {
      throw NotCallableCalled("tried to call not a function but " +
                              fnexpr->toString());
    }
    auto argEval = arg->eval(env);
    auto argId = functionExpr->argId();
    env.addToEnv(argId, argEval);
    return functionExpr->fnBody()->eval(env);
  }
  Call(std::shared_ptr<Expr> fn, std::shared_ptr<Expr> arg)
      : fn(fn), arg(arg) {}
  virtual std::string toString() {
    return "(call " + fn->toString() + " " + arg->toString() + ")";
  }
};
