module;

#include <string_view>
#include <ranges>
#include <vector>
#include <algorithm>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import custom_iterators_01;
import custom_iterators_04;
import custom_iterators_05;
import custom_iterators_06;
import custom_iterators_07;
import custom_iterators_08;
import custom_iterators_09;

//Input iterators: read only
export void custom_iterators_01_demo(){

	//std::vector<int> box1 {8,1,4,2,5,3,7,9};
    custom_iterators_01::BoxContainer<int> box1;
    //improvement::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);

    //Use iterator to access the elements
    for(auto it = box1.begin(); it!=box1.end(); ++it){
        fmt::print("{} ",*it);
    }
   
    //find algorithm: requires an input iterator
    if (std::ranges::find(box1, 8) != box1.end()) {
		fmt::println("numbers contains: {}",8);
    } else {
		fmt::println("numbers does not contain: {}",8);
    }

    //Won't work. Needs a bidirectional iterator
    //std::ranges::reverse(box1.begin(),box1.end());


    //Range based for loop
    for(auto n : box1){
		fmt::print("{} ",n);
    }
	  fmt::println("\n");

}

//Ouput iterators: write only - we go through operator* and operator-> to modify the value referenced by the iterator.
//The class in custom_iterators_01 already supports output iterators through operator* and operator->
export void custom_iterators_02_demo(){

    custom_iterators_01::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   
    std::cout << "box : " << box1 << std::endl;

    //Destination box
    custom_iterators_01::BoxContainer<int> box2;
    for(size_t i{}; i < box1.size();++i){
        box2.add(0);
    }
 
    std::cout << "box2-1 : " << box2 << std::endl;
	//The copy algorithm needs an output iterator to paste into the destination.
    std::ranges::copy(box1,box2.begin());
    std::cout << "box2-2 : " << box2 << std::endl;
}


//Forward iterators: The std::replace algorithm requires forward iterators.
export void custom_iterators_03_demo(){
  // A vector of integers with consecutive duplicates
    custom_iterators_01::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);

    std::cout << "box1 : " << box1 << std::endl;
    std::ranges::replace(box1.begin(),box1.end(),7,777);
    std::cout << "box1 : " << box1 << std::endl;
}

//Bidirectional iterators
export void custom_iterators_04_demo(){

    custom_iterators_04::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   
    std::cout << "box1 : " << box1 << std::endl;
    std::ranges::reverse(box1);
    std::cout << "box1 : " << box1 << std::endl;

    //Traverse in reverse
    std::cout << "box1 (printed reversed) : ";
    for(auto it = box1.end();it!=box1.begin(); ){
        std::cout << *(--it )<< " ";
    }
    std::cout << std::endl;

}

//Random access iterators
export void custom_iterators_05_demo(){
    custom_iterators_05::BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   
    std::cout << "box1 : " << box1 << std::endl;
    std::ranges::sort(box1.begin(),box1.end());
    //std::ranges::sort(box1);  
    //std::sort(box1.begin(),box1.end());
    std::cout << "box1 : " << box1 << std::endl;

}

//Using iterator powered container with standard views
export void custom_iterators_06_demo(){

   custom_iterators_05::BoxContainer<int> vi;
    vi.add(5);
    vi.add(1);
    vi.add(4);
    vi.add(8);
    vi.add(5);
    vi.add(3);
    vi.add(7);
    vi.add(9);
    vi.add(6);

    //std::ranges::filter_view
    std::cout <<std::endl;
    std::cout << "std::ranges::filter_view : " << std::endl;
    auto evens = [](int i){
        return (i %2) == 0;
    };
    std::cout << "vi : " ;
    custom_iterators_06::print(vi);


    std::ranges::filter_view v_evens = std::ranges::filter_view(vi,evens); //No computation
    std::cout << "vi evens : ";
    custom_iterators_06::print(v_evens); //Computation happens in the print function

    //Print evens on the fly 
    std::cout << "vi evens : " ;
    custom_iterators_06::print(std::ranges::filter_view(vi,evens));


    //std::ranges::transform_view
    std::cout <<std::endl;
    std::cout << "std::ranges::transform_view : " << std::endl;
    std::ranges::transform_view v_transformed = std::ranges::transform_view(vi,[](int i){
        return i * 10;
    });
    std::cout << "vi : " ;
    custom_iterators_06::print(vi);
    std::cout << "vi transformed : " ;
    custom_iterators_06::print(v_transformed);
    std::cout << "vi : ";
    custom_iterators_06::print(vi);


    //std::ranges::take_view
    std::cout <<std::endl;
    std::cout << "std::ranges::take_view : " << std::endl;
    std::ranges::take_view v_taken = std::ranges::take_view(vi,5);
    std::cout << "vi : " ;
    custom_iterators_06::print(vi);
    std::cout << "vi taken : ";
    custom_iterators_06::print(v_taken);

    //std::ranges::take_while_view
    std::cout <<std::endl;
    std::cout << "std::views::take_while : " << std::endl;
    std::ranges::take_while_view v_taken_while = std::ranges::take_while_view(vi,[](int i){
        return (i%2)!=0;
    });
    std::cout << "vi : ";
    custom_iterators_06::print(vi);
    std::cout << "vi taken_while : ";
    custom_iterators_06::print(v_taken_while);

    //std::ranges::drop_view : drop n first elements
    std::cout <<std::endl;
    std::cout << "std::ranges::drop_view : " << std::endl;
    std::ranges::drop_view v_drop = std::ranges::drop_view(vi,5);
    std::cout << "vi : ";
    custom_iterators_06::print(vi);
    std::cout << "vi_drop : ";
    custom_iterators_06::print(v_drop);


    //std::views::drop_while_view : drops elements as long as the predicate is met
    std::cout <<std::endl;
    std::cout << "std::ranges::drop_while_view : " << std::endl;
    std::ranges::drop_while_view v_drop_while = std::ranges::drop_while_view(vi,[](int i){
        return (i%2)!=0;
    });
    std::cout << "vi : ";
    custom_iterators_06::print(vi);
    std::cout << "v_drop_while : ";
    custom_iterators_06::print(v_drop_while);



    //Range adaptors
    //std::views::filter()
    std::cout <<std::endl;
    std::cout << "std::views::filter : " << std::endl;
    auto evens1 = [](int i){
        return (i %2) == 0;
    };
    std::cout << "vi : " ;
    custom_iterators_06::print(vi);
    std::ranges::filter_view v_evens1 = std::views::filter(vi,evens1); //No computation
    std::cout << "vi evens : ";
    custom_iterators_06::print(v_evens1); //Computation happens in the print function
    //Print evens on the fly 
    std::cout << "vi evens : " ;
    custom_iterators_06::print(std::views::filter(vi,evens1));
    //Print odds on the fly
    std::cout << "vi odds : " ;
    custom_iterators_06::print(std::views::filter(vi,[](int i){
        return (i%2)!=0;
    }));


    //Students example
    std::cout << std::endl;
    std::cout << "students example : " << std::endl;

    custom_iterators_05::BoxContainer<custom_iterators_06::Student> class_room; //  {{"Mike",12},{"John",17},{"Drake",14},{"Mary",16}};
    class_room.add(custom_iterators_06::Student("Mike",12));
    class_room.add(custom_iterators_06::Student("John",17));
    class_room.add(custom_iterators_06::Student("Drake",14));
    class_room.add(custom_iterators_06::Student("Mary",16));
    
    std::cout << std::endl;
    std::cout << "classroom : " << std::endl;
    for( auto& s : class_room){
        std::cout << "   " <<  s << std::endl;
    }

    std::ranges::sort(class_room,std::less<>{},&custom_iterators_06::Student::m_age);

    std::cout << std::endl;
    std::cout << "classroom (after sort) : " << std::endl;
    for( auto& s : class_room){
        std::cout << "   " <<  s << std::endl;
    }


    std::cout << "students under 15 : " ;
    custom_iterators_06::print(std::views::take_while(class_room,[](const custom_iterators_06::Student& s){return (s.m_age <15);}));
    //auto less_than_15_v = class_room | std::views::take_while([](const custom_iterators_06::Student& s){return (s.m_age <15);});
    //custom_iterators_06::print(less_than_15_v);
    std::cout << "End!" << std::endl;

}


//#7: Const and reverse iteators
export void custom_iterators_07_demo(){
    custom_iterators_07::BoxContainer<int> vi;
    vi.add(5);
    vi.add(1);
    vi.add(7);
    vi.add(2);
    vi.add(5);
    vi.add(3);
    vi.add(7);
    vi.add(9);
    vi.add(6);
    const custom_iterators_07::BoxContainer<int> copy(vi);

    //Use regular non const iteator
    std::cout << "forward : ";
    for(auto it = vi.begin(); it!=vi.end(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << "\n";

    //Use const iterator
    std::cout << "const forward: ";
    for(auto it = copy.begin(); it!=copy.end(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << "\n";


    //Use reverse iterator
    std::cout << "reverse : ";
    for(auto it = vi.rbegin(); it!=vi.rend(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << "\n";

    //Use const reverse iterator
    std::cout << "const reverse : ";
    for(auto it = copy.rbegin(); it!=copy.rend(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << "\n";


}


export void custom_iterators_08_demo(){

    custom_iterators_08::BoxContainer<int> vi;
    vi.add(5);
    vi.add(1);
    vi.add(7);
    vi.add(2);
    vi.add(5);
    vi.add(3);
    vi.add(7);
    vi.add(9);
    vi.add(6);

    const custom_iterators_08::BoxContainer<int> copy(vi);

    //Printing a const container
    std::cout << "data : ";
    for (auto it = copy.begin(); it!=copy.end(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;

    //Printing throgh a function
    std::cout << "copy : ";
    custom_iterators_08::print(copy);


    //Attempt to sort copy
    //std::ranges::sort(copy); // Compiler error. Can't sort a const collection
    std::ranges::sort(vi);

    std::cout << "vi : ";
    custom_iterators_08::print(vi);


    std::cout << "view taking only 3 : " ;
    for(auto i : std::views::take(vi,3)){
        std::cout << i << " " ;
    }
    std::cout << std::endl;
    
    std::cout << "End!" << std::endl;

}

export void custom_iterators_09_demo(){

    custom_iterators_09::VectorWrapper<std::string> greeting;
    greeting.add("Hello");
    greeting.add("World!");
    greeting.add("How");
    greeting.add("are");
    greeting.add("you");
    greeting.add("all");
    greeting.add("doing?");
    
    std::cout << "greeting : " << greeting << std::endl;

    std::cout << "Range based for loop : " << std::endl;
    for(auto i : greeting){
        std::cout << i << " ";
    }
    std::cout << std::endl;


    std::cout << "taking only 2 : "; 
    for(auto i : greeting | std::views::take(2)){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}