#include <iostream>


int max(int*a , int* b){
    std::cout << "max with int* called" << std::endl;
    return (*a > *b)? *a : *b;
}

int max(const int* a, const int* b){
    std::cout << "max with cont int* called" << std::endl;
    return (*a > *b)? *a : *b;
}


/*
int min(const int* a, const int* b){
    return (*a < *b)? *a : *b;
}
*/


int min(const int* const a, const int* const b){
	std::cout << "&a : " << &a << std::endl;
	std::cout << "&b : " << &b << std::endl;
    return (*a < *b)? *a : *b;
}



int main(){

/*
    int a{10};
	int b{12};

	const int c{30};
	const int d{15};

    auto result = max(&c,&c);
    */

   	const int c{30};
	const int d{15};

    const int* p_c{&c};
    const int* p_d{&d};

    std::cout << "&p_c : " << &p_c << std::endl;
    std::cout << "&p_d : " << &p_d << std::endl;

    auto result = min(p_c,p_d);


    
    return 0;
}