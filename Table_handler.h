#ifndef TABLE_HANDLER_H
#define TABLE_HANDLER_H

#include<vector>
#include"Symbol_table.h"
#include"Symbol.h"
#include<iostream>
#include<string>
#include<stdexcept>
#include<memory>

class Table_handler{
   public:
      //returns singleton instance
      static Table_handler& instance();
      //creates a new Symbol_table and push_back onto the vector
      void push_table();
      //If >1 table is on the vector this removes it, if there is only one table on vector throw an exception
      void pop_table();
      //Add symbol to the last table in the vector vis Symbol_table::insert. Return the value that insert returns
      bool insert(std::shared_ptr<Symbol> sym);
      //Iterates through symbol table vector from back to front calling lookup on each. Returns first match found. returns nullptr if symbol is undefined
      std::shared_ptr<Symbol> lookup(const std::string& name);     
      //iterate through tables in vector from back to front, printing wach
      friend std::ostream& operator<<(std::ostream& os, const Table_handler& sh);
      bool defined_in_current_scope(const std::string& name);
      //Call erase() on Symbol table with matching symbol
      void erase(const std::string& name);
      
    Table_handler(const Table_handler&) = delete;
    Table_handler& operator=(const Table_handler&) = delete;

   private:
      //Default constructor
      Table_handler();
      std::vector<std::shared_ptr<Symbol_table>> tables;
};
#endif
