// updated Mon Apr 15 20:43:21 PDT 2019

#include <memory>
#include "Event_manager.h"
#include "gpl_assert.h"
using namespace std;


/* static */ Event_manager&  Event_manager::instance()
{
  static Event_manager the_manager;
  return the_manager;
}


void Event_manager::execute_handlers(Window::Keystroke keystroke) const
{
  for(std::size_t i = 0;i < state_ptrs[keystroke].size(); i++) { 
 
	state_ptrs[keystroke][i]->execute(); 
  }
  
}


void Event_manager::add_handler(Window::Keystroke k, const Statement* s){//adds the head of a linked list of statements into appropraite 
  state_ptrs[k].push_back(s);

}


Event_manager::~Event_manager(){
  for(int i = 0; i < Window::NUMBER_OF_KEYS; ++i){
    for(std::size_t j = 0; j < state_ptrs[i].size(); ++j){
      delete state_ptrs[i][j];
    }
  }
}
