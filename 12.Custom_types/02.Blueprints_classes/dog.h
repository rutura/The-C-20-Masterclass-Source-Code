#pragma once

#include <string>
#include <string_view>

class Dog
{
public:
    Dog() = default;
    Dog(std::string_view name_param, std::string_view breed_param, int age_param);
    ~Dog();

private:
    std::string name;
    std::string breed;
    int *p_age{ nullptr };
};
