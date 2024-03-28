#ifndef ENGINEER_H
#define ENGINEER_H
#include "person.h"

//Engineer is doing private inheritance

class Engineer : public Person
{
friend std::ostream& operator<<(std::ostream& out , const Engineer& operand);
    friend struct fmt::formatter<Engineer>;

public:
    Engineer();
    Engineer(std::string_view fullname,int age,
    std::string_view address,int contract_count);
    ~Engineer();
    
    void build_something(){
        m_full_name = "John Snow"; // OK
        m_age = 23; // OK
        //m_address = "897-78-723"; Compiler error
    }

    int get_contract_count() const{
        return contract_count;
    }
    
private : 
    int contract_count{0};
};
template<>
struct fmt::formatter<Engineer> {
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Engineer &obj, FormatContext &ctx) const {
        return format_to(ctx.out(), "Engineer [Full name: {}, age: {}, address: {}, contract_count: {}]", obj.get_full_name(), obj.get_age(),obj.get_address(), obj.get_contract_count());
    }
};
#endif // ENGINEER_H
