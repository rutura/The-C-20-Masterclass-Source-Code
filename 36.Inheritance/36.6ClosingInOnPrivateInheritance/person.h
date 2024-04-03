#ifndef PERSON_H
#define PERSON_H

#include <fmt/format.h>
#include <string>
#include <string_view>
class Person
{
    friend std::ostream& operator<<(std::ostream& , const Person& person);
    friend struct fmt::formatter<Person>;
public:
    Person() = default;
    Person(std::string_view fullname,int age,
    const std::string address);
    ~Person();
    
    //Getters
    std::string get_full_name()const{
        return m_full_name;
    }
    
    int get_age()const{
        return m_age;
    }
    
    std::string get_address()const{
        return m_address;
    }
public:
    std::string m_full_name{"None"};
protected: 
    int m_age{0};
private : 
    std::string m_address{"None"};
};

/**
* Person obj fmt's output overload
- reference: https://fmt.dev/latest/api.html
*/
template <>
struct fmt::formatter<Person> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Person& obj, FormatContext& ctx) {
        return format_to(ctx.out(), "Person [Full name: {}, Age: {}, Address: {}]", obj.get_full_name(), obj.get_age(), obj.get_address());
    }
};


#endif // PERSON_H
