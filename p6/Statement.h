#ifndef STATEMENT_H
#define STATEMENT_H

class Expression;
class Variable;
class Statement {
  public:
    void append_statement(Statement* atend);
    Statement():next(nullptr) {}
    virtual void execute() const=0;
    virtual ~Statement(){ delete next; }
  protected:
    Statement* next;
};

//##
// NullStatement
//##
class NullStatement : public Statement {
  public:
    NullStatement(){}
    virtual void execute() const;
};



class Print : public Statement{
  public:
    Print(int line_number, const Expression* rhs) : line_number(line_number), rhs(rhs){}
    virtual void execute() const;
    ~Print();
  private:
    int line_number;
    const Expression* rhs;
};

class Assign : public Statement{
  public:
    Assign(Variable* lhs, Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Assign();
  private:
    Variable* lhs;
    Expression* rhs;
};

class If : public Statement{
  public:
    If(Expression* exp, Statement* if_statement) : exp(exp), if_statement(if_statement), else_statement(nullptr){}
    If(Expression* exp, Statement* if_statement, Statement* else_statement) : exp(exp), if_statement(if_statement), else_statement(else_statement){}
    virtual void execute() const;
    virtual ~If();
  private:
    Expression * exp;
    Statement* if_statement;
    Statement* else_statement;
    
};

class For : public Statement{
  public:
    For(Statement* initial_statement, Expression* exp, Statement* incr_statement, Statement* ex_statement) : initial_statement(initial_statement), exp(exp), incr_statement(incr_statement), ex_statement(ex_statement){}
    virtual void execute() const;
    virtual ~For();
  private:
    Expression* exp;
    Statement* initial_statement;
    Statement* incr_statement;
    Statement* ex_statement;
};

class Exit : public Statement{
  public:
    Exit(int line_number, Expression* exp) : line_number(line_number), exp(exp) {}
    virtual void execute() const;
    virtual ~Exit();
  private:
    Expression* exp;
    int line_number;
};




#endif
