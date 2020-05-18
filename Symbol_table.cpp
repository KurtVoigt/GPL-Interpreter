#include"Symbol_table.h"
#include<string>
#include<unordered_map>
#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
//returns nullptr if symbol is not in the table
std::shared_ptr<Symbol> Symbol_table::lookup(const std::string& name) const{
   //find the entry in the unordered map using find function in unordered map
   std::unordered_map<std::string, std::shared_ptr<Symbol>>::const_iterator got = symbols.find(name);
   if(got == symbols.end()){
      return nullptr;
   }
   else{
      
      return got->second;
   }
}

//returns false if input parameter already exists,
//must need to use a function to dereference a shared pointer
bool Symbol_table::insert(std::shared_ptr<Symbol> sym){
   //std::string s = sym->get_name(); Works
   //std::string s = *(sym).get_name(); WHY DOESN'T THIS WORK???
   std::unordered_map<std::string, std::shared_ptr<Symbol>>::const_iterator got = symbols.find(sym->get_name());
   if(got != symbols.end()) return false; //symbol is in table
   else{
      symbols.insert({sym->get_name(), sym});
      return true;
   }
}

void Symbol_table::erase(const std::string& name){
  symbols.erase(name);

}


std::ostream& operator<<(std::ostream& os, const Symbol_table& t){ //watch auto keyword
   
   std::vector<std::string> vec;
   for(auto got=t.symbols.begin(); got!=t.symbols.end(); got++){
 //os << "Pushed back" << got->first << "-------";     
      vec.push_back(got->first);
   }
      std::sort(vec.begin(), vec.end());
   for(auto i = vec.begin(); i!=vec.end(); i++){
      
      os << *(t.lookup(*i)) << '\n';
   
   }


 
    
   return os;
}

