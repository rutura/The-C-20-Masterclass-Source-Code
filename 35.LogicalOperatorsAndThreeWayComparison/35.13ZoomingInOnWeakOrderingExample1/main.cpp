#include <iostream>
#include <string>

class ComparableString {
public:
    ComparableString(const std::string& str): m_str{ str }{}

    std::weak_ordering operator<=>(const ComparableString& right_side) const{

        if (m_str.size() == right_side.m_str.size()) {
            return std::weak_ordering::equivalent;
        }
        else if (m_str.size() > right_side.m_str.size()) {
            return std::weak_ordering::greater;
        }
        else {
            return std::weak_ordering::less;
        }

    }

    bool operator==(const ComparableString& right_side) const{
        return ( m_str.size() == right_side.m_str.size());
    }

private:
    std::string m_str;
};




int main(){

	ComparableString cmp_str1("Fog");
	ComparableString cmp_str2("Dogy");
	
	std::cout << std::boolalpha;
	std::cout << "cmp_str1 > cmp_str2 : " << (cmp_str1 > cmp_str2) << std::endl;
	std::cout << "cmp_str1 < cmp_str2 : " << (cmp_str1 < cmp_str2) << std::endl;

	std::cout << "cmp_str1 == cmp_str2 : " << (cmp_str1 == cmp_str2) << std::endl;
    
    return 0;
}