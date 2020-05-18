#include<string>
#include"Symbol.h"
#include"gpl_type.h"
#include<iostream>
#include<ostream>
#include<assert.h>
//Symbol Class Definition
Symbol::Symbol(const std::string& name, double* value) : name(name), value(value), type(DOUBLE) {}

Symbol::Symbol(const std::string& name, double* value, int count) : name(name), value(value), count(count), type(DOUBLE){
   if(count < 0){
     std::cerr << "ERROR: INVALID ARRAY SIZE" ;
   }
}

Symbol::Symbol(const std::string& name, int* value) : name(name), value(value), type(INT){}

Symbol::Symbol(const std::string& name, int* value, int count) : name(name), value(value), count(count), type(INT) {
   if(count < 0){
     std::cerr << "ERROR: INVALID ARRAY SIZE" ;
   }
}
Symbol::Symbol(const std::string& name, std::string* value) : name(name), value(value), type(STRING) {}

Symbol::Symbol(const std::string& name, std::string* value, int count) : name(name), value(value), count(count), type(STRING) {
   if(count < 0){
     std::cerr << "ERROR: INVALID ARRAY SIZE" ;
   }
}

Symbol::Symbol(const std::string& name, Circle* value) : name(name), value(value), type(CIRCLE) {}

Symbol::Symbol(const std::string& name, Circle* value, int count) : name(name), value(value), count(count), type(CIRCLE) {
  if(count < 0){
    std::cerr <<"ERROR: INVALID ARRAY SIZE" ;
  }
}
Symbol::Symbol(const std::string& name, Rectangle* value) : name(name), value(value), type(RECTANGLE) {}

Symbol::Symbol(const std::string& name, Rectangle* value, int count) : name(name), value(value), count(count), type(RECTANGLE) {
  if(count < 0){
    std::cerr <<"ERROR: INVALID ARRAY SIZE" ;
  }
}
Symbol::Symbol(const std::string& name, Triangle* value) : name(name), value(value), type(TRIANGLE) {}

Symbol::Symbol(const std::string& name, Triangle* value, int count) : name(name), value(value), count(count), type(TRIANGLE) {
  if(count < 0){
    std::cerr <<"ERROR: INVALID ARRAY SIZE" ;
  }
}
Symbol::Symbol(const std::string& name, Textbox* value) : name(name), value(value), type(TEXTBOX) {}

Symbol::Symbol(const std::string& name, Textbox* value, int count) : name(name), value(value), count(count), type(TEXTBOX) {
  if(count < 0){
    std::cerr <<"ERROR: INVALID ARRAY SIZE" ;
  }
}
Symbol::Symbol(const std::string& name, Pixmap* value) : name(name), value(value), type(PIXMAP) {}

Symbol::Symbol(const std::string& name, Pixmap* value, int count) : name(name), value(value), count(count), type(PIXMAP) {
  if(count < 0){
    std::cerr <<"ERROR: INVALID ARRAY SIZE" ;
  }
}

Symbol::Symbol(const std::string& name, Animation_code* value) : name(name), value(value), type(ANIMATION_CODE) {}









Gpl_type Symbol::get_type() const{
    return type;
} 

std::string Symbol::get_name() const{
    return name;
}

int Symbol::get_count() const{
    return count;
}

symbol_type Symbol::get_value() const{
    return value;
}




std::ostream& operator<<(std::ostream& os, const Symbol& s){
  const int x = s.count;

    if(gpl_type_to_string(s.type)=="int"){
         if(x > 0){
            for(int i=0; i<x; i++){
               if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << " = " << *(s.value.int_pointer + i) ;  }

              else{ os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << " = " << *(s.value.int_pointer + i) << std::endl;}
            }
           
          }
          else {os << "int " << s.name << " = " << *s.value.int_pointer;}
    }
    else if(gpl_type_to_string(s.type)=="double"){
        if(s.count > 0){
            for(int i=0; i<x; ++i){
               if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << " = " << *(s.value.double_pointer + i)  ; }
               else{os << gpl_type_to_string(s.type)  << " "<< s.name <<"[" << i << "]" << " = " << *(s.value.double_pointer + i) << std::endl;}
             }
            
         }
          else {os << "double " << s.name << " = " << *s.value.double_pointer;}
    }
        
    else if(gpl_type_to_string(s.type)=="string"){
        if(s.count > 0){
            for(int i=0; i<x; i++){
        if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << " = " << "\"" << *(s.value.string_pointer + i)<< "\""; }

              else{ os << gpl_type_to_string(s.type) << " " << s.name <<"[" << i << "]"  << " = " << "\"" << *(s.value.string_pointer + i) << "\"" <<std::endl;}
                }
            
            
        }
        else {os << "string " << s.name << " = " << "\"" << *s.value.string_pointer << "\"";}
    }    
    
    else if(s.type==CIRCLE){
      if(x > 0){
        for(int i=0; i<x; i++){
               if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.circle_pointer + i);}

            else{ os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.circle_pointer + i) << std::endl;}
            }

      }

      else{
        os << gpl_type_to_string(s.type) << " " << s.name << *s.value.circle_pointer;
      }
    }


 else if(s.type==TRIANGLE){
      if(x > 0){
        for(int i=0; i<x; i++){
               if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.triangle_pointer + i);}

            else{ os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.triangle_pointer + i) << std::endl;}
            }

      }

      else{os <<gpl_type_to_string(s.type) << " " << s.name << *s.value.triangle_pointer;}
    }


 else if(s.type==RECTANGLE){
   if(x > 0){
      for(int i=0; i<x; i++){
        if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.rectangle_pointer + i);}

        else{ os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.rectangle_pointer + i) << std::endl;}
      }

   }
   
   else{os <<gpl_type_to_string(s.type) << " " << s.name << *s.value.rectangle_pointer;}
  }
 else if(s.type==PIXMAP){
      if(x > 0){
        for(int i=0; i<x; i++){
           if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.pixmap_pointer + i);}

           else{ os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.pixmap_pointer + i) << std::endl;}
            }

      }

     else{ os <<gpl_type_to_string(s.type) << " " << s.name << *s.value.pixmap_pointer;}
    } 
  else if(s.type==TEXTBOX){
      

     if(x > 0){
        for(int i=0; i<x; i++){
               if(i==(x-1)){os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.textbox_pointer + i);}

            else{ os << gpl_type_to_string(s.type) <<" " << s.name <<"[" << i << "]" << *(s.value.textbox_pointer + i) << std::endl;}
            }

      }
      else{os <<gpl_type_to_string(s.type) << " " << s.name << *s.value.textbox_pointer ;}
    }

  else if(s.type == ANIMATION_CODE){
    os << gpl_type_to_string(s.type) << " " << s.name;
  }
  

    else{ assert(false);}
    return os; 
}




const Constant* Symbol::as_constant() const{
  if(type == STRING){
     return new String_constant(*value.string_pointer);
  }
  else if(type == DOUBLE){
    return new Double_constant(*value.double_pointer);
  }
  else if(type == INT){
    return new Integer_constant(*value.int_pointer);
  }
  else if(type == RECTANGLE){
    return new Game_object_constant(value.rectangle_pointer);
  }
  else if(type == CIRCLE){
    return new Game_object_constant(value.circle_pointer);
  }
  else if(type == TRIANGLE){
    return new Game_object_constant(value.triangle_pointer);
  }
  else if(type == TEXTBOX){
    return new Game_object_constant(value.textbox_pointer);
  }
  else if(type == PIXMAP){
    return new Game_object_constant(value.pixmap_pointer);
  }
  else if(type == ANIMATION_CODE){
    return new Animation_block_constant(value.Animation_code_pointer);
  }
  else{  throw type;}
}


const Constant* Symbol::as_constant(int index) const{
  if(index > count-1 || index < 0) return nullptr;
  else if(type == DOUBLE){
    return new Double_constant(value.double_pointer[index]);
  }
  else if(type == INT){
    return new Integer_constant(value.int_pointer[index]);
  }
  else if(type == STRING){
    return new String_constant(value.string_pointer[index]);
  }
  else if(type == RECTANGLE){
    return new Game_object_constant(&value.rectangle_pointer[index]);
  }
  else if(type == CIRCLE){
    return new Game_object_constant(&value.circle_pointer[index]);
  }
  else if(type == TRIANGLE){
    return new Game_object_constant(&value.triangle_pointer[index]);
  }
  else if(type == TEXTBOX){
    return new Game_object_constant(&value.textbox_pointer[index]);
  }
  else if(type == PIXMAP){
    return new Game_object_constant(&value.pixmap_pointer[index]);
  }

  else { throw type;}
}

const Constant* Symbol::as_constant(const std::string attribute_name) const{ //for non-arrays
  if(type == RECTANGLE){
    return new Game_attribute_constant(value.rectangle_pointer, attribute_name);
  }
  else if(type == CIRCLE){
    return new Game_attribute_constant(value.circle_pointer, attribute_name);
  }
  else if(type == TRIANGLE){
    return new Game_attribute_constant(value.triangle_pointer, attribute_name);
  }
  else if(type == TEXTBOX){
    return new Game_attribute_constant(value.textbox_pointer, attribute_name);
  }
  else if(type == PIXMAP){
    return new Game_attribute_constant(value.pixmap_pointer, attribute_name);
  }
  else{ throw type;}


}
const Constant* Symbol::as_constant(int index, const std::string attribute_name) const{ //for arrays 
  if(index > count-1 || index < 0) return nullptr;
  
  else if(type == RECTANGLE){
    return new Game_attribute_constant(&value.rectangle_pointer[index], attribute_name);
  }
  else if(type == CIRCLE){
    return new Game_attribute_constant(&value.circle_pointer[index], attribute_name);
  }
  else if(type == TRIANGLE){
    return new Game_attribute_constant(&value.triangle_pointer[index], attribute_name);
  }
  else if(type == TEXTBOX){
    return new Game_attribute_constant(&value.textbox_pointer[index], attribute_name);

  }
  else if(type == PIXMAP){
    return new Game_attribute_constant(&value.pixmap_pointer[index], attribute_name);
  }
  else{ throw type;}


}

std::shared_ptr<Locator> Symbol::as_lvalue()
{
  if(type == STRING){
    std::shared_ptr<String_locator> p =  std::make_shared<String_locator>(*value.string_pointer);
    return p;
  }
  else if(type == DOUBLE){
    std::shared_ptr<Double_locator> p =  std::make_shared<Double_locator>(*value.double_pointer);
    return p;
  }
  else if(type == INT){
    std::shared_ptr<Integer_locator> p =  std::make_shared<Integer_locator>(*value.int_pointer);
    return p;
  }
  else if (type== ANIMATION_CODE){
     std::shared_ptr<Animation_block_locator> p =  std::make_shared<Animation_block_locator>(value.Animation_code_pointer);
    return p;

  }
  else{ throw type;}

}


std::shared_ptr<Locator> Symbol::as_lvalue(int index){
  if(index > count-1 || index < 0) return nullptr;
  else if(type == DOUBLE){
     std::shared_ptr<Double_locator> p = std::make_shared<Double_locator>(value.double_pointer[index]);
     return p;
  }
  else if(type == INT){
    std::shared_ptr<Integer_locator> p = std::make_shared<Integer_locator>(value.int_pointer[index]);
    return p;
  }
  else if(type == STRING){
    std::shared_ptr<String_locator> p = std::make_shared<String_locator>(value.string_pointer[index]);
    return p;
  }
  else { throw type;}

}

std::shared_ptr<Locator> Symbol::as_lvalue(const std::string& attribute_name){
if(type == RECTANGLE){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(value.rectangle_pointer, attribute_name);
    return p;
  }
  else if(type == CIRCLE){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(value.circle_pointer, attribute_name);
    return p;
  }
  else if(type == TRIANGLE){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(value.triangle_pointer, attribute_name);
    return p;
  }
  else if(type == TEXTBOX){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(value.textbox_pointer, attribute_name);
    return p;
  }
  else if(type == PIXMAP){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(value.pixmap_pointer, attribute_name);
    return p;
  }
  else{ throw type;}


}


std::shared_ptr<Locator> Symbol::as_lvalue(int index, const std::string& attribute_name){
  if(index > count-1 || index < 0) return nullptr;
  
  else if(type == RECTANGLE){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(&value.rectangle_pointer[index], attribute_name); return p;
  }
  else if(type == CIRCLE){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(&value.circle_pointer[index], attribute_name); return p;
  }
  else if(type == TRIANGLE){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(&value.triangle_pointer[index], attribute_name); return p;
  }
  else if(type == TEXTBOX){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(&value.textbox_pointer[index], attribute_name); return p;

  }
  else if(type == PIXMAP){
    std::shared_ptr<Game_attribute_locator> p = std::make_shared<Game_attribute_locator>(&value.pixmap_pointer[index], attribute_name); return p;
  }
  else{ throw type;}


}


Symbol::~Symbol(){
    
    if(count >0){//array, hopefully this condition is ok
       if(type == DOUBLE){
          delete[] value.double_pointer;
       }
       else if(type == INT){
          delete[] value.int_pointer;
       }
       else if(type == STRING){
          delete[] value.string_pointer;
       }
    
       else{;}
    }
    else{ //isn´t an array
       if(type == DOUBLE) {delete value.double_pointer;}
       else if(type == INT) {delete value.int_pointer;}
       else if(type == STRING) {delete value.string_pointer;}
       else if(type == ANIMATION_CODE) {delete value.Animation_code_pointer;}
       else{;}
    }
   // delete type;
   // delete count;*/
}
