#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Expression {
    virtual Expression* diff(std::string) = 0;
    virtual void print() = 0;
    virtual Expression* clone() = 0;
    virtual ~Expression() {}
};

struct Binary: public Expression {
    Binary(Expression* left, Expression* right): left(left), right(right) {}
    Expression* diff(std::string) { return nullptr; }
    Expression* left;
    Expression* right;
    ~Binary() {
        delete left;
        delete right;
    }
};

struct Unary: public Expression {
    Unary(Expression* expr): expr(expr) {}
    Expression* diff(std::string) { return nullptr; }
    Expression* expr;
    ~Unary() {
        delete expr;
    }
};

struct Add: public Binary {
    Add(Expression* left, Expression* right): Binary(left, right) {}
    Expression* clone() {
        return new Add(left->clone(), right->clone());
    }
    Expression* diff(std::string var) {
        return new Add(left->diff(var), right->diff(var));
    }
    void print() {
        cout << "(";
        left->print();
        cout << " + ";
        right->print();
        cout << ")";
    }
};

struct Sub: public Binary {
    Sub(Expression* left, Expression* right): Binary(left, right) {}
    Expression* clone() {
        return new Sub(left->clone(), right->clone());
    }
    Expression* diff(std::string var) {
        return new Sub(left->diff(var), right->diff(var));
    }
    void print() {
        cout << "(";
        left->print();
        cout << " - ";
        right->print();
        cout << ")";
    }
};

struct Mult: public Binary {
    Mult(Expression* left, Expression* right): Binary(left, right) {}
    Expression* clone() {
        return new Mult(left->clone(), right->clone());
    }
    Expression* diff(std::string var) {
        return new Add(new Mult(left->diff(var), right->clone()), new Mult(left->clone(), right->diff(var)));
    }
    void print() {
        cout << "(";
        left->print();
        cout << " * ";
        right->print();
        cout << ")";
    }
};

struct Div: public Binary {
    Div(Expression* left, Expression* right): Binary(left, right) {}
    Expression* clone() {
        return new Div(left->clone(), right->clone());
    }
    Expression* diff(std::string var) {
        Expression* top = new Sub(new Mult(left->diff(var), right->clone()), new Mult(left->clone(), right->diff(var)));
        Expression* bottom = new Mult(right->clone(), right->clone());
        return new Div(top, bottom);
    }
    void print() {
        cout << "(";
        left->print();
        cout << " / ";
        right->print();
        cout << ")";
    }
};

struct Exponent: public Unary {
    Exponent(Expression* expr): Unary(expr) {}
    Expression* clone() {
        return new Exponent(expr);
    }
    Expression* diff(std::string var) {
        return new Mult(new Exponent(expr->clone()), expr->diff(var));
    }
    void print() {
        cout << "exp(";
        expr->print();
        cout << ")";
    }
};

struct Val: public Expression {
    Val(int value): value(value) {}
    Expression* clone() {
        return new Val(value);
    }
    Expression* diff(std::string) { return new Val(0); }
    int value;
    void print() {
        cout << value;
    }
};

struct Var: public Expression {
    Var(string var): variable(var) {}
    Expression* clone() {
        return new Var(variable);
    }
    Expression* diff(std::string var) {
        return new Val(variable == var);
    }
    string variable;
    void print() {
        cout << variable;
    }
};
