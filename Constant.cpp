//File: Constant.cpp
#include "Constant.h"

Gpl_type  Constant::type() const 
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }



//game object attributes
int Game_attribute_constant::as_int() const{
   
     Gpl_type t = gop->attribute_type(attribute_name);
     if(t == INT){
       int return_value;
       gop->read_attribute(attribute_name, return_value);
       return return_value;
     }
     else{
       throw Constant::type();
     }

   
}

double Game_attribute_constant::as_double() const{
   
  Gpl_type t = gop->attribute_type(attribute_name);
     if(t == DOUBLE || t == INT){//CHANGED THIS
       double return_value;
       int return_value2;
       if (t==INT){
         gop->read_attribute(attribute_name, return_value2);
         return_value = return_value2;
       }
       else{
         gop->read_attribute(attribute_name, return_value);}
        
       return return_value;
     }
     else{

       throw Constant::type();
     }
}

std::string Game_attribute_constant::as_string() const{
   
   Gpl_type t = gop->attribute_type(attribute_name);
     if(t == INT || t == DOUBLE || t == STRING){
       std::string return_value;
       int return_int;
       double return_dub;
       if(t==INT){
         gop->read_attribute(attribute_name, return_int);
         return_value = std::to_string(return_int);
       }
       else if(t==DOUBLE){
         gop->read_attribute(attribute_name, return_dub);
         return_value = std::to_string(return_dub);
       }
       else{
          gop->read_attribute(attribute_name, return_value);
       }
       return return_value;
     }
     else{
       
       throw Constant::type();
     }
}



const Animation_code* Game_attribute_constant::as_animation_block() const{
  Gpl_type t = gop->attribute_type(attribute_name);

  Animation_code* return_value;
  if(t==ANIMATION_BLOCK){
    gop->read_attribute(attribute_name, return_value);
    return return_value;
  }
  else{
    throw Constant::type();
  }

}
