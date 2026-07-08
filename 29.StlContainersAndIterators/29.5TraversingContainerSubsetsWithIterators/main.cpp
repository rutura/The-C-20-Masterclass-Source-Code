#include <iostream>
#include <vector>
#include <array>

template <typename T>
void print_collection(const T& collection , size_t begin_adjustment,
                                    size_t end_adjustment){
    //Adjudt begining and end
    auto start_point = collection.begin() + begin_adjustment;
    auto  end_point = collection.end() - end_adjustment;
    
    std::cout << " [";
    while(start_point != end_point){
        std::cout << " " << *start_point ;
        ++start_point;
    }
    std::cout << "]" << std::endl;
}


int main(){

    std::vector<int> ints1{ 11,22,33,44,55,66,77 };
    std::array<int,6> ints2 {100,200,300,400,500,600};

    print_collection(ints1,1,3);
    print_collection(ints2,1,1);
   
    return 0;
}