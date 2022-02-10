// updated Mon Oct 14 13:01:55 PDT 2019
// * Redesign of dynamic attribute registry
// * removed set_member_variable. Have get_member_variable return member variable by reference
// updated Mon Apr 22 16:31:13 PDT 2019

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
/****

Introduction:

  class Game_object is a pure virtual base class for all gpl objects such as:

    class Circle : public Game_object
    class Triangle : public Game_object
    class Rectangle : public Game_object

  It provides support for two main parts of a gpl object
    
    1) attribute variables (named variables of type int, double, string)
    2) graphics (animation, drawing, calculations (e.g. touches))

  Users of Game_object (and the classes that inherit it) should focus
  on its public member functions.  In other words, you can use Game_object
  without fully understanding how it works.


Member variables

    Need to be able to set/get member variables knowing only the
    variable's textual name

    This arises from the fact that in a gpl script we have the textual
    names of variables but since gpl is not C++ code, we can't simply
    use "obj.x"

    Need a mechanism that is extensible.  Specifically, when a new
    class is created, need to be able to set/get its member variables
    knowing only the variable's textual name

 Solution:

    Use templates and a Prop(erty) base classe to keep a registry of variables
    that can be set/get from gpl.

    Implement this registry in class Game_object.

    Require all objects w/variables that need to be set/get from gpl
    to inherit Game_object.

  Registry

      The Register() member function maps the name of the variable
      as a string to a dynamically allocated variable. The type of
      the variable is inferred by the type of the value used to
      initialize the registered variable.
  
  Access:
      typename T represents the type of the variable being read/written.


      T& write_attribute(const std::string& name, const T& var)
      T& read_attribute(const std::string& name, T& var)

      Available as a convenience function for accessing registered variables
      T& attribute(const std::string& name)

      Exceptions thrown by read/write functions:
      + if name is unregistered: out_of_range
      + if var doesn't match member type: Gpl_type of attribute


Graphics

  All graphics are done using OpenGL display lists.

  In order to define the graphics for an object, it must override the
  pure virtual function:
  
      virtual void build_display_list() = 0;

  in this function the graphics should be drawn to the display list
  m_display_list.

  Updating display list
  
    When a member variable is changed, build_display_list() is called before
    the object is redrawn.

    A class can redefine this behavior by providing the following function:

      virtual void updated(string name) {m_display_list_dirty = true;}

    If a member variable is not linked to the graphics, then don't
    mark the display list as dirty when that variable changes

  Drawing order

    An integer is associated with each Game_object to specify its
    drawing order.  Game_objects with smaller numbers are drawn before
    Game_objects with larger numbers.  Thus the Game_object with the
    largest drawing_order number is drawn last and will thus appear on
    top of all other game objects.

****/
#include<GL/gl.h>
#include<memory>
#include "gpl_type.h"

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>

///////////////////////////////////////////////////
// Prop
///////////////////////////////////////////////////
//
//Base class for managing dynamic class properties
//
class Prop
{
  private:
    static std::unordered_map<std::type_index, Gpl_type> typemap;
  protected:
    const std::type_index proptype;
    static Gpl_type GetGPLType(std::type_index ti)
    { return typemap.at(ti); }
  public:
    Gpl_type GetGPLType() const
    { return typemap.at(proptype); }

    Prop(const std::type_index& proptype)
      :proptype(proptype)
    {}

    virtual ~Prop()
    { }
};

///////////////////////////////////////////////////
// Property<T>
///////////////////////////////////////////////////
//
//Derived template class. Each object is a property of type
//specified by the template parameter
//
template<typename T>
class Property : public Prop
{
  private:
    T data;
  public:
    virtual ~Property()
    { }

    //"The lifetime of the object returned by typeid extends to the end of the program."
    Property(const T& d)
      : Prop(std::type_index(typeid(T))), data(d) //tagger added const to all types?
    { }

    //If T does not match property type, throw Gpl_type of property
    T& PropertyVal()
    {
      //Long, sordid tale for why GetGPLType must wrap the operands in the if-statement. 
      //Bottom line: this is the least-painful way to get the const and non-const
      //Animation* to map as equivalent 
      //(T will be const on the rhs of the assign expression).
      if(GetGPLType(std::type_index(typeid(T))) != GetGPLType())
        throw GetGPLType();
      return data;
    }
    const T& PropertyVal() const
    {
      if(std::type_index(typeid(T)) != proptype)
        throw GetGPLType();
      return data;
    }
};

class Animation_code;

class Game_object
{
  public:
    Game_object(double red, double green, double blue, Gpl_type got);
    virtual ~Game_object();

    /////////////
    // Register a dynamic property
    /////////////
    template<typename T>
      void Register(const std::string& name, const T& data)
      {
        properties[name] = std::make_shared<Property<T>>(data);
      }

    /////////////
    // Deregister a dynamic property
    /////////////
    void Deregister(const std::string& name)
    {
      properties.erase(name);
    }

    /////////////
    // Return the Gpl_type of the attribute
    // + Throws out_of_range if name is unregistered 
    /////////////
    Gpl_type attribute_type(const std::string& name) const
    {
      std::shared_ptr<Prop> p=properties.at(name);
      return p->GetGPLType();
    }

    /////////////
    // Assign attribute to var
    // + Throws out_of_range if name is unregistered 
    // + Throws Gpl_type of attribute if var doesn't match member type
    /////////////
    template<typename T>
      const T& read_attribute(const std::string& name, T& var) const
      {
        std::shared_ptr<const Property<T>> p =
          std::static_pointer_cast<const Property<T>>(properties.at(name));
        return var=p->PropertyVal();
      }

    /////////////
    // Assign var to attribute
    // + Throws out_of_range if name is unregistered 
    // + Throws Gpl_type of attribute if var doesn't match member type
    /////////////
    template<typename T>
      T& write_attribute(const std::string& name, const T& var)
      {
        std::shared_ptr<Property<T>> p =
          std::static_pointer_cast<Property<T>>(properties.at(name));
        p->PropertyVal()=var;//assign before return statement to support updating the drawing order
        graphics_dirty = true;
        if (name == "drawing_order")
          update_order_in_game_objects_vector();
        updated(name);
        return p->PropertyVal();
      }

    /////////////
    // Return const attribute
    // + Throws out_of_range if name is unregistered 
    // + Throws Gpl_type of attribute if var doesn't match member type
  protected:
    template<typename T>
      const T& attribute(const std::string& name) const
      {
        std::shared_ptr<const Property<T>> p =
          std::static_pointer_cast<const Property<T>>(properties.at(name));
        return p->PropertyVal();
      }

    /////////////
    // Return mutable attribute. 
    // The benefit of this over write_attribute is that it is safe to use
    // inside the virtual updated() function.
    // + Throws out_of_range if name is unregistered 
    // + Throws Gpl_type of attribute if var doesn't match member type
  protected:
    template<typename T>
      T& attribute(const std::string& name)
      {
        std::shared_ptr<Property<T>> p =
          std::static_pointer_cast<Property<T>>(properties.at(name));
        return p->PropertyVal();
      }

  public:
    void draw();

    bool visible() {return attribute<int>("visible");}

    int touches(const Game_object *obj) const;
    int near(const Game_object *obj) const;

    // if no objects have changed, do not draw
    static bool graphics_out_of_date_with_last_rendering();

    // draw all game objects in the vector all_game_objects
    static void draw_all_game_objects();

    static void animate_all_game_objects();
    void animate();

    bool valid() const;

    friend std::ostream& operator<<(std::ostream& os, const Game_object& go);

  protected:

    void insert_into_all_game_objects_vector();
    void update_order_in_game_objects_vector();


    // each object that inherits us must implement build_display_list()
    virtual void build_display_list() = 0;

    // the default is to mark the display list as dirty when any member
    // variable changes. "h" and "w" are written to the protected data
    // members object_height and object_width respectively.
    // Subclasses can redefine this behavior if the
    // display list changes only when some members fields are changed
    virtual void updated(const std::string& name);

  protected:
    GLuint m_display_list;
    bool m_display_list_dirty;
    int  object_height;
    int  object_width;
  private:
    std::map<std::string, std::shared_ptr<Prop>> properties;

    static bool graphics_dirty;
    static std::vector<Game_object *> all_game_objects;
    static std::vector<Game_object *> deleted_game_objects;

    Game_object(const Game_object &) = delete;
    Game_object &operator=(const Game_object &) = delete;
};

#endif // #ifndef GAME_OBJECT_H
