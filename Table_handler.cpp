#include"Table_handler.h"
#include<iostream>
Table_handler::Table_handler(){
  push_table();
}

Table_handler& Table_handler::instance(){
   static Table_handler x;
   return x;
}

void Table_handler::push_table(){
    std::shared_ptr<Symbol_table> y = std::make_shared<Symbol_table>();
    tables.push_back(y);
}

void Table_handler::pop_table(){
   if(tables.size()<2){
      throw std::underflow_error("Can't pop global symbol table");
   }
   else{
      tables.pop_back();
   }
}

bool Table_handler::defined_in_current_scope(const std::string& name){
   if(tables[tables.size()-1]->lookup(name) == nullptr) return false;
   else return true;
}

bool Table_handler::insert(std::shared_ptr<Symbol> sym){

   return tables[tables.size()-1]->insert(sym);
   
  // return tables[0]->insert(sym);
}

std::shared_ptr<Symbol> Table_handler::lookup(const std::string& name){
   //Table_handler y = Table_handler::intstance();

   
   for(int i = tables.size()-1; i>=0; --i){
      
      //std::shared_ptr x = std::make_shared<Symbol>();
     std::shared_ptr<Symbol> x = tables[i]->lookup(name);
     
      if(x != nullptr) return x;
   }
   
   return nullptr;
}

void Table_handler::erase(const std::string& name){
   for(int i = tables.size()-1; i>=0; --i){
      
      //std::shared_ptr x = std::make_shared<Symbol>();
     std::shared_ptr<Symbol> x = tables[i]->lookup(name);
     
      if(x != nullptr) {tables[i]->erase(name); return;}
   }
   
   return ;

}


std::ostream& operator<<(std::ostream& os, const Table_handler& sh){
   for(auto i = sh.tables.rbegin(); i != sh.tables.rend(); ++i){
      os << *(*i);
      
   }
     
   return os;
}
