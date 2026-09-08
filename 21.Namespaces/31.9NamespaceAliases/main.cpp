#include <iostream>

namespace Level1{
    namespace Level2{
        namespace Level3{
            const double weight{33.33};
        }
    }
}


int main(){

    //Namespace aliases
    namespace Data = Level1::Level2::Level3;

    //std::cout << "weight : " << Level1::Level2::Level3::weight << std::endl;
    std::cout << "weight : " << Data::weight << std::endl;
    std::cout << "weight : " << Data::weight << std::endl;
    
    return 0;
}