#include<memory>
#include "Table_handler.h"
#include "Animation_code.h"
#include "Statement.h"

std::set<std::string> Animation_code::defined_blocklist;
std::set<std::string> Animation_code::declared_blocklist;
std::set<std::string> Animation_code::used_blocklist;

Animation_code::Animation_code(const std::string& block_name, Gpl_type parameter_type) 
  :block_name(block_name), parameter_type(parameter_type), block(new NullStatement) 
{}
void Animation_code::set_block(const Statement* blk) //in animation_block:
{ delete block; block=blk; }

std::string Animation_code::get_block_name() const
{
  return block_name;
}
Gpl_type Animation_code::get_parameter_type() const
{ return parameter_type; }

void Animation_code::set_parameter_name(const std::string& pname)//in animation_declaration:
{ parameter_name=pname; }

void Animation_code::execute(Game_object* argument) const
{
  //Implemented in P6 WHICH IS NOWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

  Table_handler& th = Table_handler::instance();
  th.push_table();
  th.insert(std::make_shared<Reference>(parameter_name,  parameter_type, argument));
  block->execute();
  th.pop_table();

}
