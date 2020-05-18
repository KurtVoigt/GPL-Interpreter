// updated 2/14/16


#include "Game_object.h"
#include "Animation_code.h"
#include "gpl_assert.h"
#include "error.h"
#include <algorithm>
#include <ostream>
#include <vector>
#include <string>
#include <memory>
using std::vector;
using std::string;


//Map of C++ type to Gpl_type
/* static */  std::unordered_map<std::type_index, Gpl_type> Prop::typemap {
    {std::type_index(typeid(int)),              INT},
    {std::type_index(typeid(std::string)),      STRING},
    {std::type_index(typeid(double)),           DOUBLE},
    {std::type_index(typeid(Animation_code*)), ANIMATION_BLOCK},
    {std::type_index(typeid(const Animation_code*)), ANIMATION_BLOCK},
};

// all game objects that have been created but not deleted
// used for (1) error checking via valid() (2) drawing all game objects
/* static */ std::vector<Game_object *> Game_object::all_game_objects;


// all game objects that have been deleted
// used for error checking via has_been_deleted()
/* static */ std::vector<Game_object *> Game_object::deleted_game_objects;

/* static */ bool Game_object::graphics_dirty = true;


void Game_object::updated(const std::string& name) 
{
  if(name=="h")
    read_attribute("h", object_height);
  if(name=="w")
    read_attribute("w", object_width);
  m_display_list_dirty = true;
}


void Game_object::insert_into_all_game_objects_vector()
{
  // all_game_objects is a vector sorted by drawing_order
  // Sorted small to large (small drawing_order drawn first/on bottom)

  // find the first iter w/a larger or equal attribute<int>("drawing_order") compared to this
  std::vector<Game_object *>::iterator iter = all_game_objects.begin();
  while (iter != all_game_objects.end()
      && (*iter)->attribute<int>("drawing_order") < attribute<int>("drawing_order"))
    iter++;

  // this object has a larger drawing_order than any object in vector
  if (iter == all_game_objects.end())
  {
    all_game_objects.push_back(this);
  }
  // the game object pointed to by iter is the first one in the vector
  // that has a drawing order larger or equal to this
  // insert before this object
  else {all_game_objects.insert(iter,this);}

}

// call when the drawing_order for a Game_object changes
// removes the object from the all_game_objects vector and
// inserts it in the correct position
void Game_object::update_order_in_game_objects_vector()
{
  // remove this from all_game_objects
  vector<Game_object *>::iterator iter =
    find(all_game_objects.begin(), all_game_objects.end(), this);
  assert(iter != all_game_objects.end());
  all_game_objects.erase(iter);

  // now put it back -- it will go in the correct place this time
  insert_into_all_game_objects_vector();
}

/* static */ bool Game_object::graphics_out_of_date_with_last_rendering()
{
  bool result = graphics_dirty;
  graphics_dirty = false;
  return result;
}

/* static */ void Game_object::animate_all_game_objects()
{
  vector<Game_object *>::iterator iter;
  for (iter = all_game_objects.begin();
      iter != all_game_objects.end();
      iter++)
  {
    Game_object *cur = *iter;
      cur->animate();
  }
}

/* static */ void Game_object::draw_all_game_objects()
{
  vector<Game_object *>::iterator iter;
  for (iter = all_game_objects.begin();
      iter != all_game_objects.end();
      iter++)
  {
      (*iter)->draw();
  }
}

Game_object::Game_object(double red /* =  0.5 */,
    double green /* = 0.5 */,
    double blue /* =  0.5 */,
    Gpl_type got) :
    m_display_list(0),
    m_display_list_dirty(true),
    object_height(10),
    object_width(10)
{
  Register("x",              0);
  Register("y",              0);
  Register("w",              10);
  Register("h",              10);
  Register("red",            red);
  Register("green",          green);
  Register("blue",           blue);
  //Specify type directly to eliminate nullptr ambiguity
  Register("animation_block", new Animation_code("NULL", got));
  Register("visible",        1);
  Register("proximity",      4);
  Register("drawing_order",  0);
  Register("user_int",       0);
  Register("user_double",  0.0);
  //option (1) for coping with const char* vs std::string
  Register<std::string> ("user_string",   "");
  Register("user_int2",      0);
  Register("user_double2", 0.0);
  //option (2) for coping with const char* vs std::string
  Register("user_string2",  std::string());
  Register("user_int3",      0);
  Register("user_double3", 0.0);
  Register("user_string3",  std::string());
  Register("user_int4",      0);
  Register("user_double4", 0.0);
  Register("user_string4",  std::string());
  Register("user_int5",      0);
  Register("user_double5", 0.0);
  Register("user_string5",  std::string());

  // OpenGL is not initialized enough yet to create our
  // display list.  Use a unique number so that draw()
  // will know it is the first time it is called.

    insert_into_all_game_objects_vector();
}


Game_object::~Game_object()
{
  if(!true)//!draw_me
    return;
  vector<Game_object *>::iterator iter =
    find(all_game_objects.begin(), all_game_objects.end(), this);
  assert(iter != all_game_objects.end());

  deleted_game_objects.push_back(*iter);

  all_game_objects.erase(iter);
}

void Game_object::draw()
{
  if (attribute<int>("visible")==false)
    return;
  if (m_display_list_dirty)
  {
    if (m_display_list == 0)
      m_display_list = glGenLists(1);

    build_display_list();
    m_display_list_dirty = false;
  }
  //   it might be more efficient to move the translation for m_x and m_y
  //   out of the display list
  //   a) if most objects move, it will probably be faster to take it out of
  //      the display list
  //   b) if most objects don't move, it will be faster to leave it in
  //   unclear if there is an efficiency problem...

  glCallList(m_display_list);
}

static bool overlap(int ax1, int ay1, int ax2, int ay2,
    int bx1, int by1, int bx2, int by2
    )
{
  return !(ax2 < bx1 || ax1 > bx2 || ay1 > by2 || ay2 < by1);
}

// since gpl does not have a bool, touches() and near() return an int to reduce
// confusion between ints and bools
int Game_object::touches(const Game_object *obj) const
{

  /*****
    LIMITATION

    touches uses the bounding box of the object which is created at object
    construction.

    The bounding box is not a very good representation of triangles or circles.
    And it does not take into account the rotation of either triangles
    or rectangles.

    It would make the touches mechanism better if objects were represented
    with a more accurate boundary.

    Idea 1:  use a polygon to represent the bounding boxes.  Each type of
    object could create and update their polygon.  When line segments of the
    polygons of two objects intersect the two objects would be considered touching.
    This approach does not handle containment (when one object is completely
    inside another).

    Idea 2: represent each object as a set of triangles.  When segments of
    triangles of two objects intersect, the objects touch.  Could also look
    for a vertex inside of another object's triangle.
   *****/


  // true if the bounding boxes of this and obj overlap
  return overlap(attribute<int>("x"), attribute<int>("y"), attribute<int>("x") + object_width, attribute<int>("y") + object_height,
      obj->attribute<int>("x"), obj->attribute<int>("y"), obj->attribute<int>("x") + obj->object_width, obj->attribute<int>("y")+obj->object_height);
}

int Game_object::near(const Game_object *obj) const
{

  // expand the bounding boxes of this and obj by their respective attribute<int>("proximity")
  // true if the expanded bounding boxes of this and obj overlap
  return overlap(attribute<int>("x") - attribute<int>("proximity"), attribute<int>("y") - attribute<int>("proximity"),
      attribute<int>("x") + object_width + attribute<int>("proximity"), attribute<int>("y") + object_height + attribute<int>("proximity"),
      obj->attribute<int>("x") - obj->attribute<int>("proximity"), obj->attribute<int>("y") - obj->attribute<int>("proximity"),
      obj->attribute<int>("x") + obj->object_width + obj->attribute<int>("proximity"),
      obj->attribute<int>("y")+obj->object_height + obj->attribute<int>("proximity"));
}

void Game_object::animate()
{
  if (attribute<Animation_code*>("animation_block"))
  {
    // Call our own animation block
    // Animation blocks are special type of statement block that ALWAYS
    // contain a pointer to a symbol in the symbol_table that represent
    // a parameter.

    // When this object calls its animation block, it must pass itself
    // <this> to the execute function of the animation_block

    attribute<Animation_code*>("animation_block")->execute(this);
  }
}

bool Game_object::valid() const
{
  vector<Game_object *>::iterator iter =
    find(all_game_objects.begin(), all_game_objects.end(), this);
  return iter != all_game_objects.end();
}

// symbol_name should include the [#] for arrays
// for example:  "rects[2]"
// for non-arrays, leave out the [#]
// for example:  "my_rectangle"
std::ostream& operator<<(std::ostream& os, const Game_object& go)
{

  
  os << std::endl << "{" << std::endl;

  auto iter=go.properties.begin();
  for (; iter != go.properties.end(); iter++)
  {
    string cur_name = iter->first;
    auto cur_member = iter->second;

    if (iter != go.properties.begin())
      os << ",\n";
    os << "    " << cur_name << " = ";
    switch (cur_member->GetGPLType())
    {
      case INT:
        {
          os << "int(" << go.attribute<int>(cur_name) << ")";
          break;
        }
      case DOUBLE:
        {
          os << "double(" << go.attribute<double>(cur_name) << ")";
          break;
        }
      case STRING:
        {
          os << "string(\"" << go.attribute<std::string>(cur_name) << "\")";
          break;
        }
      case ANIMATION_BLOCK:
        {
            //os << go.attribute<Animation_code*>(cur_name)->get_block_name();
            os << go.attribute<Animation_code*>("animation_block")->get_block_name();
          break;
        }
      default:
        // there is a programming bug if this is ever executed
        assert(false);
    }
  } // for loop iterating through all registered member variables
  os << std::endl << "}";
  return os;
}

