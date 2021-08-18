#include <iostream>

const double distance{}; // Declaration and definition

extern int item_count; // Declaration of some variable defined in some
                       // other translation unit


//Functions have external linkage by default
void print_distance(){
    std::cout << "distance (other_file) : " << distance << " &distance  :"
     << &distance << std::endl;
}

void print_item_count(){
    std::cout << "item_count(other_file) : " << item_count << " &item_count : "
        << &item_count << std::endl;
}

