// updated Thu Apr 25 21:55:30 PDT 2019

#include "Triangle.h"
#include "gpl_assert.h"
using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>

Triangle::Triangle(double red, double green, double blue)
  : Game_object(red, green, blue, TRIANGLE)
{
    Register("size",     10);
    Register("rotation", 0.0);
    Register("skew",     1.0);
}


//###// Note on the comments below with //###//. commented-out code 
//###// make more appropriately reflects demoting "h" and "w" to 
//###// write-only values. However, the legacy code didn't do that, so
//###// tests starting in project 4 fail with different output of the 
//###// symbol table. After the redesign deployment is complete, I'll 
//###// come back, uncomment the above, and regenerate the tests.

void Triangle::updated(const string& name)
{
  //if "w" changes, immediately overwrite it
  //because in this derived class, w is derived from other values
  if(name=="size" || name=="w")
    //###//attribute<int>("w")=
      read_attribute("size", object_width);
  //if "h" changes, immediately overwrite it
  //because in this derived class, h is derived from other values
  if(name=="y" || name=="size" || name=="skew" || name=="h")
  {
    double top_point_y = 1.118 * attribute<int>("size") * attribute<double>("skew") + attribute<int>("y");
    //###//attribute<int>("h")=
      object_height=int(top_point_y) - attribute<int>("y");
  }
    
  m_display_list_dirty = true;
}

/* virtual */ void Triangle::build_display_list()
{
  assert(m_display_list);

  double midpoint_x = attribute<int>("x") + attribute<int>("size")/2.0;
  double top_point_y = 1.118 * attribute<int>("size") * attribute<double>("skew") + attribute<int>("y");

  // assume size or skew changed:  recalculate the height and width
  attribute<int>("w")=object_width=attribute<int>("size");

  attribute<int>("h")=object_height=int(top_point_y) - attribute<int>("y");

  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  if (attribute<double>("rotation") != 0)
  {
    double center_x = midpoint_x;
    double center_y = attribute<int>("y") + ((top_point_y - attribute<int>("y")) * .5);
    glTranslated(center_x, center_y, 0);
    glRotated(attribute<double>("rotation"), 0, 0, 1);
    glTranslated(-center_x, -center_y, 0);
  }
  glColor3f(attribute<double>("red"), attribute<double>("green"), attribute<double>("blue"));
  glBegin(GL_TRIANGLES);
    glVertex2i(attribute<int>("x"), attribute<int>("y"));
    glVertex2i(attribute<int>("x") + attribute<int>("size"), attribute<int>("y"));
    glVertex2i(int(midpoint_x), int(top_point_y));
  glEnd();
  glPopMatrix();
  glEndList();
}
