#include <algorithm>
#include <vector>
#include <ranges>
#include "boxcontainer.h"


void print(auto  view){
    for(auto i : view){ // Computation happens here.
        fmt::print("{} ", i);
    }
    fmt::println("");
}

struct Student{
    friend std::ostream& operator<<(std::ostream& out, const Student& s){
        out << "Student [ name : " << s.m_name << ", age : " << s.m_age << "]";
        return out;
    }
    friend struct fmt::formatter<Student>;
    auto operator <=>(const Student& s) const= default;
    std::string m_name;
    unsigned int m_age;
};

template<>
struct fmt::formatter<Student>
{
  constexpr auto parse(format_parse_context& ctx){return ctx.begin(); }
  template<typename FormatContext>
  auto format(const Student& obj, FormatContext& ctx)
  {
    return format_to(ctx.out(), "Student [name: {}, age: {}]", obj.m_name, obj.m_age);
  }
};

int main(){

    BoxContainer<int> vi;
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
    /*
    fmt::println("");
    fmt::println("std::ranges::filter_view : " );
    auto evens = [](int i){
        return (i %2) == 0;
    };
    fmt::print("vi : " );
    print(vi);


    std::ranges::filter_view v_evens = std::ranges::filter_view(vi,evens); //No computation
    fmt::print("vi evens : ");
    print(v_evens); //Computation happens in the print function

    //Print evens on the fly 
    fmt::print("vi evens : " );
    print(std::ranges::filter_view(vi,evens));
    */


    //std::ranges::transform_view
    /*
    fmt::println("");
    fmt::println( "std::ranges::transform_view : " );
    std::ranges::transform_view v_transformed = std::ranges::transform_view(vi,[](int i){
        return i * 10;
    });
    fmt::print("vi : " );
    print(vi);
    fmt::print( "vi transformed : ") ;
    print(v_transformed);
    fmt::print("vi : ");
    print(vi);
    */


    //std::ranges::take_view
    /*
    fmt::println("");
    fmt::println( "std::ranges::take_view : " );
    std::ranges::take_view v_taken = std::ranges::take_view(vi,5);
    fmt::print("vi : " );
    print(vi);
    fmt::print ("vi taken : ");
    print(v_taken);
    */

    //std::ranges::take_while_view
    /*
    fmt::println("");
    fmt::println("std::views::take_while : ");
    std::ranges::take_while_view v_taken_while = std::ranges::take_while_view(vi,[](int i){
        return (i%2)!=0;
    });
    fmt::print("vi : ");
    print(vi);
    fmt::print("vi taken_while : ");
    print(v_taken_while);
    */

    //std::ranges::drop_view : drop n first elements
    /*
    fmt::println("");
    fmt::println( "std::ranges::drop_view : ");
    std::ranges::drop_view v_drop = std::ranges::drop_view(vi,5);
    fmt::print("vi : ");
    print(vi);
    fmt::print("vi_drop : ");
    print(v_drop);
    */


    //std::views::drop_while_view : drops elements as long as the predicate is met
    /*
    fmt::println("");
    fmt::println( "std::ranges::drop_while_view : " );
    std::ranges::drop_while_view v_drop_while = std::ranges::drop_while_view(vi,[](int i){
        return (i%2)!=0;
    });
    fmt::print("vi : ");
    print(vi);
    fmt::println("v_drop_while : ");
    print(v_drop_while);
    */



    //Range adaptors
    //std::views::filter()
    /*fmt::println("");
    fmt::println( "std::views::filter : " );
    auto evens1 = [](int i){
        return (i %2) == 0;
    };
    fmt::print("vi : " );
    print(vi);
    std::ranges::filter_view v_evens1 = std::views::filter(vi,evens1); //No computation
    fmt::print("vi evens : ");
    print(v_evens1); //Computation happens in the print function
    //Print evens on the fly 
    fmt::print("vi evens : " );
    print(std::views::filter(vi,evens1));
    //Print odds on the fly
    fmt::print( "vi odds : " );
    print(std::views::filter(vi,[](int i){
        return (i%2)!=0;
    }));*/


    //Students example
    fmt::println("");
    fmt::println( "students example : " );

    BoxContainer<Student> class_room; //  {{"Mike",12},{"John",17},{"Drake",14},{"Mary",16}};
    class_room.add(Student("Mike",12));
    class_room.add(Student("John",17));
    class_room.add(Student("Drake",14));
    class_room.add(Student("Mary",16));
    
    fmt::println("");
    fmt::println( "classroom : " );
    for( auto& s : class_room){
        fmt::println( "   {}" ,  s );
    }

    std::ranges::sort(class_room,std::less<>{},&Student::m_age);

    fmt::println("");
    fmt::println( "classroom (after sort) : " );
    for( auto& s : class_room){
        fmt::println( "   {}" ,  s );
    }


    fmt::println( "students under 15 : " );
    print(std::views::take_while(class_room,[](const Student& s){return (s.m_age <15);}));
    /*
    auto less_than_15_v = class_room | std::views::take_while([](const Student& s){return (s.m_age <15);});
    print(less_than_15_v);
    */
    fmt::println( "End!" );
 
    
    
   

    
   


    return 0;
}