module;

#include <fmt/format.h>
#include <string>
#include <cassert>

export module op_overloading_5;

namespace op_overloading_5{

    export class Scores
    {
    public:
    Scores() = delete;
    Scores(const std::string &course_name) : m_course_name{ course_name } {}

    /*
    double& operator[](size_t index){
        assert((index >= 0) &&(index < 20));
        return m_scores[index];
    }

    double operator[](size_t index) const{
        assert((index >= 0) &&(index < 20));
        return m_scores[index];
    }
    */

    //These two implementations allow us to use the subscript operator,
    //both const and non-const objects
    double &operator[](size_t index);
    double operator[](size_t index) const;


    void print_info() const
    {
        fmt::print("{} : [", m_course_name);
        for (size_t i{}; i < 20; ++i) { fmt::print("{}  ", m_scores[i]); }
        fmt::println("]");
    }

    private:
    std::string m_course_name;
    double m_scores[20]{};
    };

    //Implementations
    double &Scores::operator[](size_t index)
    {
    assert((index >= 0) && (index < 20));
    return m_scores[index];
    }

    double Scores::operator[](size_t index) const
    {
    assert((index >= 0) && (index < 20));
    return m_scores[index];
    }
    
} // namespace op_overloading_5
