//File: Variable.cpp
#include "Variable.h"
#include"Expression.h"
#include"Constant.h"
#include "error.h"
#include<string>
#include <cmath>
#include <iostream>
#include"gpl_type.h"
#include"Locator.h"
/******************constructors****************************/
Variable::Variable(const std::string& symbol_name) : symbol_name(symbol_name), array_index_expression(nullptr)  {}

Variable::Variable(const std::string& symbol_name, Expression* index_expr) : symbol_name(symbol_name), array_index_expression(index_expr)  {}





const Constant* Variable::evaluate() const{
  if(array_index_expression == nullptr){

    if(symbol_name == "") return ret(new Integer_constant(0));
    else{ 
      return ret(symbol()->as_constant());
    }
  }

  else{
    if(symbol_name == "") 
    {
      return ret(new Integer_constant(0));

    }
    else {
      const Constant* OutOfBounds = symbol()->as_constant(array_index_expression->evaluate()->as_int());
      if(OutOfBounds == nullptr){
        if(symbol()->get_count() == -1){ //symbol is not an array
          Error::error(Error::VARIABLE_NOT_AN_ARRAY,symbol()->get_name());
        } 
        else if(symbol()->get_count() - 1 < array_index_expression->evaluate()->as_int() ){//value is out of bounds
          Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(array_index_expression->evaluate()->as_int()));
        }
        return symbol()->as_constant();
      }

      else{
        return ret(symbol()->as_constant(array_index_expression->evaluate()->as_int())); // array entry
      }
    }
  } 
}




Gpl_type Variable::type() const{
  if(symbol_name == "") return INT;
  else{
  return symbol()->get_type();

  }
}

Variable::~Variable(){
  delete array_index_expression;
}



std::shared_ptr<Locator> Variable::modify(){
      assert(symbol_name!="");


      if(array_index_expression == nullptr){//not an array
        return symbol()->as_lvalue();
      }
      const Constant* OutOfBounds = symbol()->as_constant(array_index_expression->evaluate()->as_int());
      if(OutOfBounds == nullptr){
        if(symbol()->get_count() == -1){ //symbol is not an array
          Error::error(Error::VARIABLE_NOT_AN_ARRAY,symbol()->get_name());
        } 
        else if(symbol()->get_count() - 1 < array_index_expression->evaluate()->as_int() ){//value is out of bounds
          Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(array_index_expression->evaluate()->as_int()));
        }
        return symbol()->as_lvalue();
      }

      else{
        return symbol()->as_lvalue(array_index_expression->evaluate()->as_int()); // array entry
      }
    

}


Member_variable::Member_variable(const std::string& symbol_name, std::string& data_member_name)  : Variable::Variable(symbol_name), data_member_name(data_member_name) {}
Member_variable::Member_variable(const std::string& symbol_name, Expression* index_expr, std::string& data_member_name) : Variable(symbol_name, index_expr) ,data_member_name(data_member_name)  {}

 

Gpl_type Member_variable::type() const
{
  const Constant* const_val=nullptr;
  if(array_index_expression==nullptr)
    const_val=symbol()->as_constant(data_member_name);
  else
    const_val=symbol()->as_constant(0, data_member_name);
  Gpl_type ret_type=const_val->type();
  delete const_val;
  return ret_type;
}


const Constant* Member_variable::evaluate() const{

  if(array_index_expression == nullptr){//not an array

    if(symbol_name == "") return ret(new Integer_constant(0));
    else{ 
      return ret(symbol()->as_constant(data_member_name));
    }
  }

  else{
    if(symbol_name == "") 
    {
      return ret(new Integer_constant(0));

    }
    else {//array
      const Constant* OutOfBounds = symbol()->as_constant(array_index_expression->evaluate()->as_int(), data_member_name);
      if(OutOfBounds == nullptr){
        if(symbol()->get_count() != -1){
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name,std::to_string(array_index_expression->evaluate()->as_int()));
        return symbol()->as_constant(0, data_member_name); //just 0?
        }
        else{
          Error::error(Error::VARIABLE_NOT_AN_ARRAY,symbol()->get_name());
          return ret(symbol()->as_constant(data_member_name));
        }
      }
      else{
        return ret(symbol()->as_constant(array_index_expression->evaluate()->as_int(), data_member_name )); // array entry
      }
    }
  } 
}
std::shared_ptr<Locator> Member_variable::modify(){
      assert(symbol_name!="");


      if(array_index_expression == nullptr){//not an array
        return symbol()->as_lvalue(data_member_name);
      }
      const Constant* OutOfBounds = symbol()->as_constant(array_index_expression->evaluate()->as_int(), data_member_name);
      if(OutOfBounds == nullptr){
        if(symbol()->get_count() != -1){ //symbol is an array
          Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name,std::to_string(array_index_expression->evaluate()->as_int()));
          return symbol()->as_lvalue(0, data_member_name); //just 0?
        }
        else{
          Error::error(Error::VARIABLE_NOT_AN_ARRAY,symbol()->get_name());
          return symbol()->as_lvalue(data_member_name);

        } 
      }
       
    else{
        return symbol()->as_lvalue(array_index_expression->evaluate()->as_int(), data_member_name); // array entry
    }
    

}
