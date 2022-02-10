#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include<memory>
#include<unordered_map>
#include<iostream>
#include<string>
#include"Symbol.h"
class Symbol_table {
  public:
    Symbol_table(){}
    std::shared_ptr<Symbol> lookup(const std::string& name) const;
    bool insert(std::shared_ptr<Symbol> sym);
    friend std::ostream& operator<<(std::ostream& os, const Symbol_table&);
    void erase(const std::string& name);
    //prevent compiler from generating these functions
    Symbol_table(const Symbol_table&) = delete;
    Symbol_table& operator=(const Symbol_table&) = delete;
  private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
};

#endif
