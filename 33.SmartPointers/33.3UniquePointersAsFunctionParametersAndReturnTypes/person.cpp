#include "person.h"
#include "dog.h"
Person::Person(std::string name) : m_name{name}
{
}

void Person::adopt_dog( std::unique_ptr<Dog> dog){
    fmt::println( "{}{}{}",m_name , " just adopted the dog " , dog->get_name() );
}


Person::~Person()
{
   
}

