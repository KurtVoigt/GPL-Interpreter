// updated Tue Oct  1 22:56:57 PDT 2019
// updated Mon Apr 15 20:37:30 PDT 2019
// updated Sun Nov 10 08:23:54 PST 2019

/***
  This file is a placeholder for the Event_manager singleton class required
  in phase 5 (p5).

  class Window uses class Event_manager.  Since p4 uses class Window
  this minimally-implemented class allows p4 to work.

  Use this file and Event_manager.cpp w/o modification in p4.

  These files serve as a starting point for the Event_manager class in p5.

***/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include"Statement.h"
#include "Window.h" // for Keystroke enum

class Statement;

class Event_manager
{
  public:
    static Event_manager& instance();

    void execute_handlers(Window::Keystroke keystroke) const;
    void add_handler(Window::Keystroke k, const Statement* s);

    ~Event_manager();

    Event_manager(const Event_manager&) = delete; 
    const Event_manager &operator=(const Event_manager&) = delete;

  private:
    std::vector<std::vector<const Statement*> > state_ptrs{std::vector<std::vector<const Statement*> >(Window::NUMBER_OF_KEYS)};
    Event_manager(){};
};

#endif
