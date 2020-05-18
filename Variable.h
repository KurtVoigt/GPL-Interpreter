//FILE: Variable.h
#ifndef VARIABLE_H
#define VARIABLE_H
#include "Expression.h"
#include<memory>
#include"Symbol.h"
#include"Table_handler.h"
#include"Symbol_table.h"
#include"Locator.h"
class Variable : public Expression {
  public:
    Variable(const std::string& symbol_name); //initialize unused array_index_expression to nullptr
    Variable(const std::string& symbol_name, Expression* index_expr);
    virtual const Constant* evaluate() const;
    virtual std::shared_ptr<Locator> modify();
    virtual Gpl_type type() const;
    virtual ~Variable();
    std::string get_name(){return symbol_name;};
    virtual std::string get_data_name(){return "";};
    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
  protected: //allow derived class access

    std::string symbol_name;
    Expression* array_index_expression;

    //The symbol() function eases access to the symbol
    //use it within Variable's member functions
    std::shared_ptr<Symbol> symbol()
    { return Table_handler::instance().lookup(symbol_name); }
    std::shared_ptr<Symbol> symbol() const
    { return Table_handler::instance().lookup(symbol_name); }
};



class Member_variable : public Variable {
  public:
    virtual const Constant* evaluate() const override;
    Member_variable(const std::string& symbol_name, std::string& data_member_name);
    Member_variable(const std::string& symbol_name, Expression* index_expr, std::string& data_member_name);
    virtual Gpl_type type() const override;
    virtual std::shared_ptr<Locator> modify() override;
    std::string get_data_name(){return "." + data_member_name;};
  protected:
    

  private:
    std::string data_member_name;
    
};














#endif
