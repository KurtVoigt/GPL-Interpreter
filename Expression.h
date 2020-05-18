//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "gpl_type.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual Gpl_type type() const=0; //pure virtual, abstract, derived classes must iveride/implement this function, without =0 it is only invited to
    virtual ~Expression();//invited to make own destructor
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
  protected:
    //a wrapper around returned constants
    const Constant* ret(const Constant* new_evald_constant) const;
    //keep pointer to evaluate's created constant it can be released
    mutable const Constant* evaluated_constant;
};




/************************************UNARY OPERATORS************/
class Unary_operator : public Expression{
  public:
    Unary_operator(Expression* value) : value(value) {};
    virtual const Constant * evaluate() const=0; 
    virtual ~Unary_operator() {delete value;}
  protected:
    const Expression* value;
  
};

class Negate : public Unary_operator{
  public:
    Negate(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Not : public Unary_operator{
  public:
    Not(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Sine : public Unary_operator{
  public:
    Sine(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Cosine : public Unary_operator{
  public:
    Cosine(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Tangent : public Unary_operator{
  public:
    Tangent(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Arc_cosine : public Unary_operator{
  public:
    Arc_cosine(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Arc_sine : public Unary_operator{
  public:
    Arc_sine(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Arc_tangent : public Unary_operator{
  public:
    Arc_tangent(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Square_root : public Unary_operator{
  public:
    Square_root(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Absolute_value : public Unary_operator{
  public:
    Absolute_value(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Floor : public Unary_operator{
  public:
    Floor(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Random : public Unary_operator{
  public:
    Random(Expression* value) : Unary_operator(value) {};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};






/*****************BINARY OPERATORS******************************/
class Binary_operator : public Expression {
  public:
    Binary_operator(Expression* lhs, Expression* rhs) :lhs(lhs), rhs(rhs) {};
    virtual const Constant* evaluate() const=0;
    virtual ~Binary_operator() { delete lhs; delete rhs; }
  protected:
    const Expression* lhs;
    const Expression* rhs;
};

class Near : public Binary_operator{
  public:
    Near(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};

class Touches : public Binary_operator{
   public:
    Touches(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};

class Plus : public Binary_operator {
  public:
    Plus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Divide : public Binary_operator {
  public:
    Divide(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Or : public Binary_operator {
  public:
    Or(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Minus : public Binary_operator {
public:
    Minus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};
class Modulus : public Binary_operator {
  public:
    Modulus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};
class And : public Binary_operator {
  public:
    And(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Less_than : public Binary_operator {
  public:
    Less_than(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};
class Less_equal : public Binary_operator {
  public:
    Less_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};
class Greater_than : public Binary_operator {
  public:
    Greater_than(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};

class Greater_equal : public Binary_operator {
  public:
    Greater_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};

class Equal : public Binary_operator {
  public:
    Equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};

class Not_equal : public Binary_operator {
  public:
    Not_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;

};
#endif
