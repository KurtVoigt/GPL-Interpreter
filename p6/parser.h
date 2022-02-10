// updated 2/14/2016

/*
  ALWAYS include parser.h instead of gpl.tab.h

  Here is why:

    Since the union created by bison contains several gpl objects,
    a forward class declaration, or including the .h file must be 
    done before the union is created.

*/

#ifndef PARSER_H
#define PARSER_H

// for each type used in the union, you will need to 
// put the appropriate include here
// For example, the union must hold a C++ string, so <string> is included
//   since it is bad programming practice to include "using namespace std"
//   in a .h file, you will have to put "std::string" in the union instead
//   of "string"

#include <string>
#include<set>
#include<algorithm>
#include"gpl_type.h"
#include"Symbol.h"
#include"Symbol_table.h"
#include"Table_handler.h"
#include"Constant.h"
#include"assert.h"
#include"Variable.h"
#include"Game_object.h"
#include"Circle.h"
#include"Triangle.h"
#include"Rectangle.h"
#include"Textbox.h"
#include"Pixmap.h"
#include"Window.h"
#include"Statement.h"
#include"Event_manager.h"
#include"Animation_code.h"
struct Parameter {
      Expression* expression;
      std::string name;
      Parameter* next;
      ~Parameter() { delete next; }
};

// put new included ABOVE this line
#include "gpl.tab.h"

#endif // #ifndef PARSER_H
