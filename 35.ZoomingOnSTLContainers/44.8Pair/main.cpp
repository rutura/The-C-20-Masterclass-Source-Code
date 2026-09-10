#include <iostream>
#include <vector>
#include <utility>


int main(){

    //Code1 : Create pair
    std::cout << "creating pairs:" << std::endl;
    std::pair<int,std::string> pair1{0,"Book shelf"};
    
    auto pair2 = std::make_pair(1,"Table"); // Deduces the template arguments

    //std::cout << "pair1 : " << pair1 << std::endl;

    std::cout << " pair1 : (" << pair1.first << "," << pair1.second << ")" << std::endl;
    std::cout << " pair2 : (" << pair2.first << "," << pair2.second << ")" << std::endl;

    //Code2 : auto[] syntax - collect components of a pair into variables.
    std::cout << std::endl;
    std::cout << "auto[] syntax - collect components of a pair into variables : " << std::endl;
    auto [int_var, string_var] = pair1;
    std::cout << "pair1 (auto[] syntax) : (" << int_var << "," << string_var << ")" << std::endl;
    
    

    //Code3 : template argument deduction (C++17)
    std::cout << std::endl;
    std::cout << "template argument deduction : " << std::endl;
    
    std::pair student(33165, std::string("John Snow"));// Deducing the template arguments
    
    std::cout << "student ID : " << student.first << std::endl;
    std::cout << "Student name : " << student.second << std::endl;


    //Code4 : collection of pairs
    std::cout << std::endl;
    std::cout << "collection of pairs : " << std::endl;
    
    std::vector<std::pair<int,std::string>> collection {{10,"Earth"},{20,"Spins"},
                                                        {30,"From"},{40,"Left"},
                                                        {50,"To"},{60,"Right"}};
    //Traverse : syntax1
    std::cout << std::endl;
    std::cout << "syntax1 : " << std::endl;
    std::cout << "collection : [";
    for(const auto& elt : collection){
        std::cout << " (" << elt.first << "," << elt.second << ")";
    }
    std::cout << "]" << std::endl;


    //Traverse : syntax2
    std::cout << std::endl;
    std::cout << "syntax2 : " << std::endl;
    std::cout << "collection : [";
    for( auto[key,value] : collection){
        std::cout << " (" << key << "," << value << ")";
    }
    std::cout << "]" << std::endl;
   
    return 0;
}