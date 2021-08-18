#ifndef CIVIL_ENGINEER_H
#define CIVIL_ENGINEER_H

#include "engineer.h"
class CivilEngineer : public Engineer
{
    friend std::ostream& operator<<(std::ostream&, const CivilEngineer& operand);
public:
    CivilEngineer();
    CivilEngineer(std::string_view fullname,int age,
    std::string_view address,int contract_count, std::string_view speciality);
    CivilEngineer(const CivilEngineer& source);
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

#endif // CIVIL_ENGINEER_H
