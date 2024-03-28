#ifndef CIVIL_ENGINEER_H
#define CIVIL_ENGINEER_H

#include "engineer.h"
class CivilEngineer : public Engineer
{
    friend std::ostream& operator<<(std::ostream&, const CivilEngineer& operand);
    friend struct fmt::formatter<CivilEngineer>;

public:
    CivilEngineer();
    CivilEngineer(std::string_view fullname,int age,
    std::string_view address,int contract_count, std::string_view speciality);
    ~CivilEngineer() ;
    
    void build_road(){
        //get_full_name(); // Compiler error
        ///m_full_name = "Daniel Gray"; //Compiler error
        //m_age = 45; // Compiler error

        add(10,2);
        add(10,2,4);
    }

    public : 
        //using Person::do_something; // Compiler error
	
private : 
    std::string m_speciality{"None"};

};

template<>
struct fmt::formatter<CivilEngineer> {
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const CivilEngineer &obj, FormatContext &ctx) const {
        return format_to(ctx.out(), "CivilEngineer [ Full name: {}, age: {}, address: {}, contract_count: {}, speciality: {}]", obj.get_full_name(), obj.get_age(), obj.get_address(), obj.get_contract_count(), obj.m_speciality);
    }
};
#endif // CIVIL_ENGINEER_H
