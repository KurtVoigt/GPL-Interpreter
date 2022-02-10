// Mon May 13 20:08:35 PDT 2019

#include "gpl_type.h"

//replace header w/cassert: Sat Sep 21 16:25:04 PDT 2019
//include "gpl_assert.h"
#include<cassert>
using namespace std;

string gpl_type_to_string(Gpl_type gpl_type)
{
  switch (gpl_type)
  {
    case NO_TYPE: return "no type";
    case INT: return "int";
    case DOUBLE: return "double";
    case STRING: return "string";
    case ANIMATION_BLOCK: return "animation_block";
    case ANIMATION_CODE: return "animation code";
    case GAME_OBJECT: return "game_object";
    case CIRCLE: return "circle";
    case RECTANGLE: return "rectangle";
    case TRIANGLE: return "triangle";
    case TEXTBOX: return "textbox";
    case PIXMAP: return "pixmap";
    default: assert(false); return "error";
  }
}

string status_to_string(Status status)
{
  switch(status)
  {
    case OK: return "OK";
    case MEMBER_NOT_OF_GIVEN_TYPE: return "MEMBER_NOT_OF_GIVEN_TYPE";
    case MEMBER_NOT_DECLARED: return "MEMBER_NOT_DECLARED";
    default: assert(false);
  }
  assert(false);
  return ""; // to prevent a compilation warning
}

string operator_to_string(Operator_type op)
{
  switch(op)
  {
    case PLUS: return "+";
    case MINUS: return "-";
    case DIVIDE: return "/";
    case MULTIPLY: return "*";
    case MOD: return "%";
    case UNARY_MINUS: return "-";
    case NOT: return "!";
    case AND: return "&&";
    case OR: return "||";
    case EQUAL: return "==";
    case NOT_EQUAL: return "!=";
    case LESS_THAN: return "<";
    case LESS_EQUAL: return "<=";
    case GREATER_THAN: return ">";
    case GREATER_EQUAL: return ">=";
    case NEAR: return "near";
    case TOUCHES: return "touches";
    case SIN: return "sin";
    case COS: return "cos";
    case TAN : return "tan";
    case ASIN : return "asin";
    case ACOS : return "acos";
    case ATAN : return "atan";
    case SQRT : return "sqrt";
    case ABS: return "abs";
    case FLOOR: return "floor";
    case RANDOM: return "random"; 
    default: assert(false);
  }
  assert(false);
  return ""; // to prevent a compilation warning
}
