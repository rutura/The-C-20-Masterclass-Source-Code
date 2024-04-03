#include "person.h"
#include "dog.h"
Person::Person(std::string name) : m_name{name}
{
}

void Person::adopt_dog( std::unique_ptr<Dog> dog){
    fmt::println( "{} just adopted the dog {}",m_name, dog->get_name() );
}


Person::~Person()
{
   
}

