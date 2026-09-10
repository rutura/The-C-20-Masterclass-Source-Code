#include <iostream>
#include <vector>

template <typename T>
void print_vec( const std::vector<T>& vec){
    for(size_t i{}; i < vec.size();++i){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;    
}

template <typename T>
void print_raw_array(const T* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << std::endl;
}


int main(){

    //Constructing vectors
    std::vector<std::string> vec_str {"The","sky","is","blue","my","friend"};
    std::cout << "vec1[1]  : " << vec_str[1] << std::endl;
    print_vec(vec_str);

    std::cout << "------" << std::endl;

    std::vector<int> ints1;
    std::cout << "ints1 : ";
    print_vec(ints1); // Won't print anything, the vector has no content

    std::vector<int> ints2 = { 1,2,3,4 };
    std::vector<int> ints3{ 11,22,33,44 };
    
    std::cout << "ints2 : ";
    print_vec(ints2);

    std::cout << "ints3 : ";
    print_vec(ints3);


    std::vector<int> ints4(20, 55); // A vector with 20 items, all initialized to 55
    std::cout << "ints4 : ";
    print_vec(ints4);
    
    //Be careful about uniform initialization
    std::vector<int> ints5{20, 55}; // A vector with 2 items : 20 and 55
    std::cout << "ints5 : ";
    print_vec(ints5);


    //Accessing elements
    std::cout << std::endl;
    std::cout << "Accessing elements in a vector: " << std::endl;
    std::cout << "vec_str[2] : " << vec_str[2] << std::endl;
    std::cout << "vec_str.at(3) : " << vec_str.at(3) << std::endl;
    std::cout << "vec_str.front() : " << vec_str.front() << std::endl;
    std::cout << "vec_str.back() : " << vec_str.back() << std::endl;

    //Using the data method
    std::cout << "using raw array : " << std::endl;
    print_raw_array(vec_str.data(),vec_str.size());


    //Adding and removing stuff
    std::cout << std::endl;
    std::cout << "Adding and removing stuff : " << std::endl;
    
    std::cout << "ints1 : " ;
    print_vec(ints1);
    
    
    //Pushing back
    ints1.push_back(100);
    ints1.push_back(200);
    ints1.push_back(300);
    ints1.push_back(500);
    std::cout << "ints1 : " ;
    print_vec(ints1);
    
    //Poping back
    ints1.pop_back();
    std::cout << "ints1 : " ;
    print_vec(ints1);

   
    return 0;
}