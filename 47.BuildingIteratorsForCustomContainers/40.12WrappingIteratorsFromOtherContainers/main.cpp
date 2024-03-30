#include <vector>
#include <algorithm>
#include <ranges>
#include <fmt/format.h>


template <typename T>
class VectorWrapper{
  friend struct fmt::formatter<VectorWrapper>;

public: 
    //Iterator methods
    std::vector<T>::iterator begin() { return m_items.begin(); }
    std::vector<T>::iterator end()   { return m_items.end(); }

    //Const overloads
    std::vector<T>::const_iterator begin() const{ return m_items.cbegin(); }
    std::vector<T>::const_iterator end() const  { return m_items.cend(); }


    std::vector<T>::const_iterator cbegin() { return m_items.cbegin(); }
    std::vector<T>::const_iterator cend()   { return m_items.cend(); }
 
    friend std::ostream& operator<< (std::ostream& out, const VectorWrapper<T>& vec){
        out << "Items : " ;
        for (auto i : vec.m_items){
            out << i << " ";
        }
        return out;
    }  
    
    void add( T item){
        m_items.push_back(item);
    }
private : 
    std::vector<T> m_items;
};

template<typename T>
struct fmt::formatter<VectorWrapper<T>> {
  constexpr auto parse(format_parse_context& ctx){return ctx.begin(); }
  template<typename FormatContext>
  auto format(const VectorWrapper<T>& obj, FormatContext& ctx) {
    return format_to(ctx.out(),"VectorWrapper: [size: {}, capacity: {}, items: {}]", obj.m_items.size(), obj.m_items.capacity(), fmt::join(obj.m_items | std::views::transform([](const T& elem) {
            return fmt::format("{}", elem);
        }), " "));
  }
};


int main(){

	VectorWrapper<std::string> greeting;
    greeting.add("Hello");
    greeting.add("World!");
    greeting.add("How");
    greeting.add("are");
    greeting.add("you");
    greeting.add("all");
    greeting.add("doing?");
    
    fmt::println( "greeting : {}", greeting );

    fmt::println( "Range based for loop : " );
    for(auto i : greeting){
        fmt::print( "{} ", i);
    }
    fmt::println("");


    fmt::println( "taking only 2 : " );
    for(auto i : greeting | std::views::take(2)){
        fmt::print( "{} ", i);
    }
    fmt::println("");
   
    return 0;
}