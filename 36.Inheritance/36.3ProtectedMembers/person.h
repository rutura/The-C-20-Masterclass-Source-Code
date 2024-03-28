#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <fmt/format.h>

class Person
{
    friend std::ostream& operator<<(std::ostream& out, const Person& person);

    friend struct fmt::formatter<Person>;
public:
    Person();
    Person(std::string& first_name_param, std::string& last_name_param);
    ~Person();
    
    //Getters
    std::string get_first_name() const{
        return first_name;
    }
    
    std::string get_last_name() const{
        return last_name;
    }
	
    //Setters
    void set_first_name(std::string_view fn){
        first_name = fn;
    }
    void set_last_name(std::string_view ln){
        last_name = ln;
    }
protected : 
    std::string first_name{"Mysterious"};
    std::string last_name{"Person"};
};

template<>
struct fmt::formatter<Person> {
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Person &obj, FormatContext &ctx) const {
        return format_to(ctx.out(), "Person [{} {}]", obj.first_name, obj.last_name);
    }
};
#endif // PERSON_H
