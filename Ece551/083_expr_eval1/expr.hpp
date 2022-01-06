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

class PlusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
  std::string toString() const {
    std::stringstream sso;
    sso << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return sso.str();
  }

  PlusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
};
