#include <iostream>


int main(int argc , char * argv[]){

    std::cout << "We have " << argc << " parameters in our program" << std::endl;

    for(size_t i {0}; i < argc ; ++i){
        std::cout << "parameter [" << i << "] :" <<  argv[i] << std::endl;
    }
    
    return 0;
}