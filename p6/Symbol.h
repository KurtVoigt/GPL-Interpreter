/* Kurt Voigtritter, project 2 - Header file for the Symbol
class*/
#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include "gpl_type.h"
#include "Expression.h"
#include "Constant.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Game_object.h"
#include "Pixmap.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Locator.h"
#include "Animation_code.h"
//hopefully union goes here



union symbol_type {
    double* double_pointer;
    int* int_pointer;
    std::string* string_pointer;
    Circle* circle_pointer;
    Rectangle* rectangle_pointer;
    Triangle* triangle_pointer;
    Textbox* textbox_pointer;
    Pixmap* pixmap_pointer;
    Animation_code* Animation_code_pointer;
    Game_object* game_object_pointer;
//constructors to ease initialization of union variables
    symbol_type(double* val) : double_pointer(val){};
    symbol_type(int* val) : int_pointer(val){};
    symbol_type(std::string* val) : string_pointer(val){};
    symbol_type(Circle* val) : circle_pointer(val){};
    symbol_type(Rectangle* val) : rectangle_pointer(val){};
    symbol_type(Triangle* val) : triangle_pointer(val){};
    symbol_type(Textbox* val) : textbox_pointer(val){};
    symbol_type(Pixmap* val) : pixmap_pointer(val){};
    symbol_type(Animation_code* val) : Animation_code_pointer(val){};
    symbol_type(Game_object* val) : game_object_pointer(val){};
};





//symbol class declaration
class Symbol{
    public:
        Symbol(const std::string& name, double* value); //constructor for double var
        Symbol(const std::string& name, double* value, int count); //const for double array
        Symbol(const std::string& name, int* value);//construc for int
        Symbol(const std::string& name, int* value, int count);// construc for int array
        Symbol(const std::string& name, std::string* value);//construc for string
        Symbol(const std::string& name, std::string* value, int count);//construc for array of strings (is this needed?)
	//constructors for game object types
	//circle
        Symbol(const std::string& name, Circle* value);
        Symbol(const std::string& name, Circle* value, int count);
        //rectangle
        Symbol(const std::string& name, Rectangle* value);
        Symbol(const std::string& name, Rectangle* value, int count);
	//trianglettt
        Symbol(const std::string& name, Triangle* value);
        Symbol(const std::string& name, Triangle* value, int count);
	//textbox
        Symbol(const std::string& name, Textbox* value);
        Symbol(const std::string& name, Textbox* value, int count);
	//pixmap
        Symbol(const std::string& name, Pixmap* value);
        Symbol(const std::string& name, Pixmap* value, int count);
        //animation code
        Symbol(const std::string& name, Animation_code* value);

        Gpl_type get_type() const;
        std::string get_name() const;
        int get_count() const;
        symbol_type get_value() const;
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol&);
        //prevent compiler from generating these functions
        Symbol(const Symbol&) = delete;
        Symbol& operator =(const Symbol&) = delete;
        
        const Constant* as_constant() const;
        const Constant* as_constant(int index) const;
        const Constant* as_constant(           const std::string attribute_name) const; //for non-arrays
        const Constant* as_constant(int index, const std::string attribute_name) const; //for arrays 

        std::shared_ptr<Locator> as_lvalue();                                             //non-array: int, double, or string
        std::shared_ptr<Locator> as_lvalue(int index);                                    //array element: int, double, or string
        std::shared_ptr<Locator> as_lvalue(const std::string& attribute_name); //non-array: game object
        std::shared_ptr<Locator> as_lvalue(int index, const std::string& attribute_name); //array element: game object
  
    private:
        std::string name;// name of the var
        Gpl_type type;//the type of the var. see gpl_type.h
	int count = -1; //used to store the size if the variable is in an array
    
    protected:
        symbol_type value;//contents of var
        Symbol(const std::string& name, Gpl_type type, Game_object* argument) : name(name), type(type), value(argument) {}
};

class Reference : public Symbol{
  public:
    Reference(const std::string& parameter_name, Gpl_type parameter_type, Game_object* gop)
        : Symbol(parameter_name, parameter_type, gop) {}
        virtual ~Reference(){value.game_object_pointer=nullptr;}

};







#endif
