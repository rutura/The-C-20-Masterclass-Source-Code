#include <fmt/format.h>
#include <algorithm>
#include <vector>
#include <ranges>

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

    //Source collection
    std::vector<int> numbers {1,9,3,7,2,5,4,6,89};
    fmt::println( "numbers : {}",  numbers );


    //Iterators returned by begin() are input iterators. The requirement is that we are
    //able to read through them. That's al std::ranges::find needs.
    //Show possible implementations at cppreference.
    /*
    if (std::ranges::find(numbers.cbegin(),numbers.cend(), 8) != numbers.cend()) {
        fmt::println( "numbers contains: {}" , 8 );
    } else {
        fmt::println( "numbers does not contain: {}" , 8 );
    }
    */


    //Output iterator : std::ranges::copy
    //Iterator through which we can write
    /*fmt::println( "---------------(copy)-----------" );
    std::vector<int> dest(numbers.size());
    //std::vector<int> dest; //  BAD! Probably a crash
    fmt::println( "numbers : {}" , numbers );
    fmt::println( "dest : {}" , dest );

    //dest.begin() has to be an output iterator, have to be able to write though it
    std::ranges::copy(numbers.cbegin(),numbers.cend(),dest.begin()); // Compiler Error dest.cbegin()
                                                                    // is not an output iterator
    fmt::println( "numbers : {}" , numbers );
    fmt::println( "dest : {}" , dest );*/


    //Forward iteator : std::ranges::replace , std::ranges::fill
    /*
    fmt::println( "---------------(replace)-------------" );
    fmt::println( "numbers : {}" , numbers );

    //replacing every instance of 7 with 345. The iterator needs an
    //operator++ to move forward. See possible implementation
    std::ranges::replace(numbers.begin(),numbers.end(),7,345);
    fmt::println( "numbers : {}" , numbers );
    */

   //Bidirectional iterator
    /*
    fmt::println( "---------------(bi-directional)-------------" );

    fmt::println( "numbers : {}" , numbers );
    auto it_first = numbers.begin();
    auto it_last  = numbers.end();
    while (it_last-- != it_first) {
        fmt::println( "{} ", *it_last );
    }

    fmt::println("");
    std::ranges::reverse(numbers.begin(),numbers.end());
    fmt::println( "numbers : {}" , numbers );
    */

    //Random access iteator : std::ranges::sort
    //Contiguous iterator : C++ 20 don't have a concrete example for this
    /*
    fmt::println( "---------------(sort)-------------" );
    fmt::println( "numbers : {}" , numbers );

    //Sorting the collection
    std::ranges::sort(numbers);
    fmt::println( "numbers : {}" , numbers );
    */

    return 0;
}