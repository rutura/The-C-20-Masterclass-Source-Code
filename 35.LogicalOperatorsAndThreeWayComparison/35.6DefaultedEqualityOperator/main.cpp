#include <fmt/format.h>


class Item {
public : 
    Item() = default;
    Item(int i) : Item(i,i,i){}
    Item ( int a_param, int b_param, int c_param) : a(a_param), b(b_param), c(c_param){}

    //Equality, default : member wise comparison for equality
    bool operator==(const Item& right_operand) const = default;
    
private:
    int a{ 1 };
    int b{ 2 };
    int c{ 3 };
};



int main(){

  Item i1{1,2,3};
  Item i2{1,2,33};

  fmt::println( "i1 == i2 : {}" , (i1 == i2) );
  fmt::println( "i1 != i2 : {}" , (i1 != i2) );
  fmt::println( "i1 == 12 : {}" , (i1 == 12) );
  fmt::println( "36 == i2 : {}" , (36 == i2) ); // Watch out : i2==36
  fmt::println( "i1 != 12 : {}" , (i1 != 12) );
  fmt::println( "36 != i2 : {}" , (36 != i2) );
   
    return 0;
}