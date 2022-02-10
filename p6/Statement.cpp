#include<iostream>
#include <cstdlib>
#include "Statement.h"
#include "Constant.h"
#ifdef P5
#include "Locator.h"
#endif
#include "Variable.h"
#include "Window.h"
#include "Event_manager.h"
#include"error.h"
void Statement::append_statement(Statement* atend)
{
  Statement* current=this;
  while(current->next != nullptr)
    current=current->next;
  current->next=atend;
}

//##
// NullStatement
//##
void NullStatement::execute() const
{//change
}

void Print::execute() const{
  std::cout << "print[" << line_number << "]: " << rhs->evaluate()->as_string() << std::endl;
  if(next) next->execute();

}

Print::~Print(){
  delete rhs;
}


void Assign::execute() const{
  Gpl_type lt = lhs->type();
  Gpl_type rt = rhs->type();
  /*if(gpl_type_to_string(lt) != gpl_type_to_string(rt)){//error
    Error::error(Error::ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(rt), gpl_type_to_string(lt));
  }*/
  

  std::shared_ptr<Locator> left = lhs->modify();
  
  if(lt == INT)
    left->mutate(rhs->evaluate()->as_int());
  if(lt==DOUBLE)
    left->mutate(rhs->evaluate()->as_double());
  if(lt==STRING)
    left->mutate(rhs->evaluate()->as_string());
  if(lt==ANIMATION_BLOCK){
    const Constant* rhs_constant = rhs->evaluate();
    left->mutate(rhs_constant->as_animation_block());
  }
  if(next!=nullptr) next->execute();  
    
}

Assign::~Assign(){
//delete rhs;
//delete lhs;
}


void If::execute() const{
  if(exp->evaluate()->as_int()){ //expression is true
    if_statement->execute();
  }
  else if(!exp->evaluate()->as_int() && else_statement !=nullptr){//expression is false and there is an else clause
    else_statement->execute();
  }
  else{//expression is false and there is no else statement do nothing
   ;
  }
  if(next!=nullptr) next->execute();
}

If::~If(){
delete if_statement;
delete else_statement;
}

void For::execute() const{
 for(initial_statement->execute(); exp->evaluate()->as_int(); incr_statement->execute()){
    ex_statement->execute();
  }
  if(next!=nullptr) next->execute();

}

For::~For(){
;//what to delete here without breaking things

}


void Exit::execute() const{
  Event_manager::instance().execute_handlers(Window::TERMINATE);
  std::cout  << "gpl[" << line_number << "]: exit(" << exp->evaluate()->as_int() << ")" << std::endl;
  exit(exp->evaluate()->as_int());
  
}

Exit::~Exit(){
  ;// change
}











