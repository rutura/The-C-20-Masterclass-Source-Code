#include "item.h"

std::ostream& operator<<( std::ostream& out, const Item& operand){
    out << "Item : [" << (*operand.m_data) << "]";
    return out;
}

bool operator==(const Item& left, const Item& right){
    return (*left.m_data) == (*right.m_data);
}
