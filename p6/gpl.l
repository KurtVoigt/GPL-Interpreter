
%option noyywrap
%option nodefault

%{
#include "error.h"    // this file contains some standardized error reporting
#include "parser.h"   //this file includes gpl.tab.h

#include <iostream>

Error error_handler; // error reporting object

// The line_count variable keeps track of what input line flex is reading.
// It will be used for reporting the line numbers of errors.
// 
//   To use in other source files, declare the variable with "extern" in front
//   of it to indicate that it is defined in a different source file: 
//      extern int line_count;
int line_count = 1;

void illegal_token_error()
{
  // have the error handling object report the problem
  // note: it uses line_count as a global variable
  error_handler.error(Error::ILLEGAL_TOKEN, yytext);

  // create a string to hold the current text
  // put that string in the yylval union so it can be used by parser (.y file)
  // NOTE THAT IF THE NAMES OF THE MEMBERS OF YOUR UNION ARE DIFFERENT,
  // YOU WILL HAVE TO CHANGE union_string TO WHATEVER YOU HAVE NAMED
  // YOUR string* MEMBER
  yylval.union_string = new std::string(yytext);
}


%}
Digit [0-9]+
%%
 


\n {line_count++;}
 /*begin pattern/action rules*/

int {return T_INT;}
double {return T_DOUBLE;}
string {return T_STRING;}
triangle {return T_TRIANGLE;}
pixmap {return T_PIXMAP;}
circle {return T_CIRCLE;}
rectangle {return T_RECTANGLE;}
textbox {return T_TEXTBOX;}

 /* keywords KEEP AN EYE ON FORWARD*/
forward {yylval.union_int = line_count; return T_FORWARD;}
initialization {return T_INITIALIZATION;}
termination {return T_TERMINATION;}
on {return T_ON;}
animation {return T_ANIMATION;}
if {return T_IF;}
for {return T_FOR;}
else {return T_ELSE;}
exit {yylval.union_int = line_count; return T_EXIT;}
print {yylval.union_int = line_count; return T_PRINT;}
true {return T_TRUE;}
false {return T_FALSE;}

 /* event keys */
space {return T_SPACE;}
leftarrow {return T_LEFTARROW;}
rightarrow {return T_RIGHTARROW;}
uparrow {return T_UPARROW;}
downarrow {return T_DOWNARROW;}
leftmouse_down {return T_LEFTMOUSE_DOWN;}
middlemouse_down {return T_MIDDLEMOUSE_DOWN;}
rightmouse_down {return T_RIGHTMOUSE_DOWN;}
leftmouse_up {return T_LEFTMOUSE_UP;}
middlemouse_up {return T_MIDDLEMOUSE_UP;}
rightmouse_up {return T_RIGHTMOUSE_UP;}
mouse_move {return T_MOUSE_MOVE;}
mouse_drag {return T_MOUSE_DRAG;}
f1 {return T_F1;}
akey {return T_AKEY;}
skey {return T_SKEY;}
dkey {return T_DKEY;}
fkey {return T_FKEY;}
hkey {return T_HKEY;}
jkey {return T_JKEY;}
kkey {return T_KKEY;}
lkey {return T_LKEY;}
wkey {return T_WKEY;}
zkey {return T_ZKEY;}

 /*PUNCTUATION*/
"(" { return T_LPAREN; }
")" { return T_RPAREN; }
"{" { return T_LBRACE;}
"}" { return T_RBRACE; } 
"[" { return T_LBRACKET; }
"]" { return T_RBRACKET; }
";" { return T_SEMIC; }
"," { return T_COMMA; }
"." { return T_PERIOD; }

 /* assignment operators
  * unlike C/C++/Java, assignment operators are NOT part of expressions
  * (no precedence level required)
  * unlike C/C++/Java, ++ and -- are not expressions operators
  * they are assignments operators, SIGNIFICANCE?
  */
= {return T_ASSIGN;}
"+"= {return T_PLUS_ASSIGN;}
-= {return T_MINUS_ASSIGN;}
"+""+" {return T_PLUS_PLUS;}
-- {return T_MINUS_MINUS;}

 /* unary operators with textual names */
 /* (no precedence level required) */
sin {return T_SIN;}
cos {return T_COS;}
tan {return T_TAN;}
asin {return T_ASIN;}
acos {return T_ACOS;}
atan {return T_ATAN;}
sqrt {return T_SQRT;}
abs {return T_ABS;}
floor {return T_FLOOR;}
random {return T_RANDOM;}

 /* graphical operators (also, add precedence level in .y file) */
touches {return T_TOUCHES;}
near {return T_NEAR;}

 /* mathematical operators (also,!!! add precedence level in .y file) */
"*" {return T_MULTIPLY;}
"/" {return T_DIVIDE;}
"+" {return T_PLUS;}
"-" {return T_MINUS;}
"%" {return T_MOD;}

 /* logical operators (also,??? add precedence level in .y file) */

"<" {return T_LESS;}
> {return T_GREATER;}
(<=) {return T_LESS_EQUAL;}
>= {return T_GREATER_EQUAL;}
== {return T_EQUAL;}
!= {return T_NOT_EQUAL;}
! {return T_NOT;}
&& {return T_AND;}
"||" {return T_OR;}


 /* The following tokens require "complex"
  * regular expressions to match them. See
  * the project writeup for the requirements
  * of these regular expressions
  KEEP EYE ON DOUBLE, MAY BE BACKSLASH NOT QUOTES
  int, double, string, identifier, comment, tab
 don't need to do negative int/double?
 [[:digit:]]
 \"([^\\\"]|\\.)*\"
  */

[0-9]+ {yylval.union_int=std::stoi(yytext); return T_INT_CONSTANT;}
([0-9]+([.][0-9]*)?|[.][0-9]+) {yylval.union_double=std::stod(yytext); return T_DOUBLE_CONSTANT;}
\"[^"\n]*\" {std::string temp(yytext); yylval.union_string=new std::string(temp.substr(1, temp.size()-2)); return T_STRING_CONSTANT;}
[_a-zA-Z][_0-9a-zA-Z]* {std::string temp(yytext); yylval.union_string= new std::string(temp); return T_ID;}
\/\/.*$ 
[ \t] 


 /* This should be the last pattern. If the lexer reaches this pattern
    there has been an error
  */
.               {illegal_token_error(); return T_ERROR;}

%%
