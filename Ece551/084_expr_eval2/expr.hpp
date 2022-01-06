#include <ctype.h>
#include <stdio.h>

#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual ~Expression(){};
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
  long num;

 public:
  std::string toString() const {
    std::stringstream sso;
    sso << num;
    return sso.str();
  }
  explicit NumExpression(long readnum) : num(readnum) {}
};

class ArithmExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  char op;
  ~ArithmExpression() {
    delete lhs;
    delete rhs;
  }
  std::string toString() const {
    std::stringstream sso;
    sso << "(" << lhs->toString() << " " << op << " " << rhs->toString() << ")";
    return sso.str();
  }

  ArithmExpression(Expression * lhs, Expression * rhs, char op) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->op = op;
  }
};

class PlusExpression : public ArithmExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : ArithmExpression(lhs, rhs, '+') {}
};

class MinusExpression : public ArithmExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : ArithmExpression(lhs, rhs, '-') {}
};
class TimesExpression : public ArithmExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : ArithmExpression(lhs, rhs, '*') {}
};
class DivExpression : public ArithmExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : ArithmExpression(lhs, rhs, '/') {}
};
