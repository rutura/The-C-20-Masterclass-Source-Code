#include <iostream>

//Definition
auto max(int& a, int& b){
    if(a>b){
        return a;
    }else{
        return b; // Will return a copy.
    }
}

int main(){

    int x{5};
    int y{9};

    int int_val = max(x,y);
   
    return 0;
}

