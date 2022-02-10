// File: Expression.cpp
#define _USE_MATH_DEFINES
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include"Game_object.h"
#include<string>
#include <cmath>
#include <iostream>

using std::string;

Expression::~Expression(){delete evaluated_constant;}

// This wrapper ensures that Constant objects created by evaluate() are
// properly released when a subsequent call to evaluate() will otherwise
// overwrite the pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/

/***********UNARY OPERATIONS*******************/
const Constant* Negate::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==STRING)
    return ret(new String_constant("-" + value_constant->as_string()));
  if(t==DOUBLE)
    return ret(new Double_constant(-1.0 * value_constant->as_double()));
  return ret(new Integer_constant(-1 * value_constant->as_int()));
}
Gpl_type Negate::type() const{
  Gpl_type t = value->type();
  if(t==STRING) return STRING;
  if(t==DOUBLE) return DOUBLE;
  return INT;
}


const Constant* Not::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Integer_constant(!(value_constant->as_double())));
  return ret(new Integer_constant(!(value_constant->as_int())));
}
Gpl_type Not::type() const{

  return INT;
}

const Constant* Sine::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant(sin(value_constant->as_double()*M_PI/180.0)));
  return ret(new Double_constant(sin(value_constant->as_int()*M_PI/180.0)));
}
Gpl_type Sine::type() const{

  return DOUBLE;
}

const Constant* Cosine::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant(cos(value_constant->as_double()*M_PI/180.0)));
  return ret(new Double_constant(cos(value_constant->as_int()*M_PI/180.0)));
}
Gpl_type Cosine::type() const{

  return DOUBLE;
}
const Constant* Tangent::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant(tan(value_constant->as_double()*M_PI/180.0)));
  return ret(new Double_constant(tan(value_constant->as_int()*M_PI/180.0)));
}
Gpl_type Tangent::type() const{

  return DOUBLE;
}
/*study why you have to seperate it this way to get correct output, you don't remember trig*/
const Constant* Arc_cosine::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant((acos(value_constant->as_double())*180.0/M_PI)));
  return ret(new Double_constant((acos(value_constant->as_int())*180.0/M_PI)));
}
Gpl_type Arc_cosine::type() const{

  return DOUBLE;
}

const Constant* Arc_sine::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant((asin(value_constant->as_double())*180.0/M_PI)));
  return ret(new Double_constant((asin(value_constant->as_int())*180.0/M_PI)));
}
Gpl_type Arc_sine::type() const{

  return DOUBLE;
}

const Constant* Arc_tangent::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant((atan(value_constant->as_double())*180.0/M_PI)));
  return ret(new Double_constant((atan(value_constant->as_int())*180.0/M_PI)));

   /* return ret(new Double_constant((atan(value_constant->as_double())*M_PI/180.0)));
  return ret(new Double_constant((atan(value_constant->as_int())*M_PI/180.0)));*/
}
Gpl_type Arc_tangent::type() const{

  return DOUBLE;
}

const Constant* Square_root::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Double_constant(sqrt(value_constant->as_double())));
  return ret(new Double_constant(sqrt(value_constant->as_int())));

}
Gpl_type Square_root::type() const{

  return DOUBLE;
}

const Constant* Absolute_value::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE){
    return ret(new Double_constant(fabs(value_constant->as_double())));}
  return ret(new Integer_constant(abs(value_constant->as_int())));

}
Gpl_type Absolute_value::type() const{
  Gpl_type t = value->type();
  if(t==DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Floor::evaluate() const{
  Gpl_type t = value->type();
  const Constant* value_constant = value->evaluate();
  if(t==DOUBLE)
    return ret(new Integer_constant(floor(value_constant->as_double())));
  return ret(new Integer_constant(floor(value_constant->as_int())));

}
Gpl_type Floor::type() const{

  return INT;
}

const Constant* Random::evaluate() const{
  const Constant* value_constant = value->evaluate();
  int x = value_constant->as_double();
  if(x < 1) x = 2;
  return ret(new Integer_constant(rand()%x));
  

}
Gpl_type Random::type() const{

  return INT;
}

/******BINARY OPERATIONS**********************
************************************************************************************88888
*******************************************************************************************8
**********************************************************************88
*****************************************/


const Constant* Near::evaluate() const{
  return new Integer_constant(lhs->evaluate()->as_game_object()->near(rhs->evaluate()->as_game_object()));


}

const Constant* Touches::evaluate() const{
return new Integer_constant(lhs->evaluate()->as_game_object()->touches(rhs->evaluate()->as_game_object()));

}

Gpl_type Near::type() const{
  return INT;
}

Gpl_type Touches::type() const{
  return INT;
}

const Constant* Plus::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new String_constant(lhs_constant->as_string() + rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() + rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() + rhs_constant->as_int()));
}

Gpl_type Plus::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Multiply::evaluate() const
{
   Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  //if(lht==STRING || rht==STRING)
    
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() * rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() * rhs_constant->as_int()));

}

Gpl_type Multiply::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  
 
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

Gpl_type Divide::type() const{
  Gpl_type lht= lhs->type();
  Gpl_type rht = rhs->type();
  if(lht==DOUBLE || rht==DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Divide::evaluate() const{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  
  if(lht == DOUBLE || rht == DOUBLE) 
    return ret(new Double_constant(lhs_constant->as_double() / rhs_constant->as_double()));
    
  return ret(new Integer_constant(lhs_constant->as_int() / rhs_constant->as_int()));
}

const Constant* Or::evaluate() const{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();

  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() || rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() || rhs_constant->as_int()));
}

Gpl_type Or::type() const{
  return INT;
}

const Constant* Minus::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  
  if(lht == DOUBLE || rht == DOUBLE) 
    return ret(new Double_constant(lhs_constant->as_double() - rhs_constant->as_double()));
    
  return ret(new Integer_constant(lhs_constant->as_int() - rhs_constant->as_int()));

}


Gpl_type Minus::type() const{
  Gpl_type lht= lhs->type();
  Gpl_type rht = rhs->type();
  if(lht==DOUBLE || rht==DOUBLE) return DOUBLE;
  return INT;

}

const Constant* Modulus::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  return ret(new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int()));
}

Gpl_type Modulus::type() const{
  return INT;
}

const Constant* And::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() && rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() && rhs_constant->as_int()));

} 
Gpl_type And::type() const{
  return INT;
}

const Constant* Less_than::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==STRING || rhs->type()==STRING) return ret(new Integer_constant(lhs_constant->as_string() < rhs_constant->as_string()));
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() < rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() < rhs_constant->as_int()));

} 
Gpl_type Less_than::type() const{
  return INT;
}

const Constant* Less_equal::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==STRING || rhs->type()==STRING) return ret(new Integer_constant(lhs_constant->as_string() <= rhs_constant->as_string()));
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() <= rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() <= rhs_constant->as_int()));

} 
Gpl_type Less_equal::type() const{
  return INT;
}

const Constant* Greater_than::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==STRING || rhs->type()==STRING) return ret(new Integer_constant(lhs_constant->as_string() > rhs_constant->as_string()));
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() > rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() > rhs_constant->as_int()));

} 
Gpl_type Greater_than::type() const{
  return INT;
}

const Constant* Greater_equal::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==STRING || rhs->type()==STRING) return ret(new Integer_constant(lhs_constant->as_string() >= rhs_constant->as_string()));
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() >= rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() >= rhs_constant->as_int()));

} 
Gpl_type Greater_equal::type() const{
  return INT;
}

const Constant* Equal::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==STRING || rhs->type()==STRING) return ret(new Integer_constant(lhs_constant->as_string() == rhs_constant->as_string()));
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() == rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() == rhs_constant->as_int()));

} 
Gpl_type Equal::type() const{
  return INT;
}

const Constant* Not_equal::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==STRING || rhs->type()==STRING) return ret(new Integer_constant(lhs_constant->as_string() != rhs_constant->as_string()));
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE) return ret(new Integer_constant(lhs_constant->as_double() != rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() != rhs_constant->as_int()));

} 
Gpl_type Not_equal::type() const{
  return INT;
}
