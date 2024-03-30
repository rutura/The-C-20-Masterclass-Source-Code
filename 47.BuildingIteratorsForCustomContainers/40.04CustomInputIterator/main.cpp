#include <algorithm>
#include <vector>
#include <ranges>
#include "boxcontainer.h"

template <typename T>
std::ostream& operator<<( std::ostream& out,const  std::vector<T>& vec){
    out << " [ ";
    for(auto i : vec){
        out << i  << " ";
    }
    out << "]";
    return out;
}
template <typename T>
struct fmt::formatter<std::vector<T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const std::vector<T>& vec, FormatContext& format_context) {
    return format_to(format_context.out(), "[{}]", fmt::join(vec | std::views::transform([](const T& elem) {
        return fmt::format("{}", elem);
    }), " "));
  }
};


int main(){

    //std::vector<int> box1 {8,1,4,2,5,3,7,9};
    BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   

    fmt::println( "box : {}",  box1 );

    //find algorithm
    if (std::ranges::find(box1, 8) != box1.end()) {
        fmt::println( "numbers contains: {}",  8 );
    } else {
        fmt::println( "numbers does not contain: {}",  8 );
    }


    //std::ranges::reverse(box1.begin(),box1.end());


    //Range based for loop
    for(auto n : box1){
        fmt::println("{} ", n);
    }
    fmt::println("");

    return 0;
}