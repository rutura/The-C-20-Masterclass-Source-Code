/*
    . Basics about inheritance:     
        . In C++, a class can inherit from, derive from, or extend another class.
        . The new class (child/derived/subclass) automatically gains the 
            public and protected data members and functions of the existing 
            class (parent/base/superclass).
        . Extending a class allows the child class to focus on differences from the parent class.
        . To extend a class, the parent class is specified in the child class 
            definition using the inheritance syntax.
        . In our example, Person is the parent class and Player is the child class.
        . Player has access to the public and protected members of Person.
            . From a Player object, one can call the get_first_name() and get_last_name() functions, 
                even though they are defined in the Person class.
*/
module;

#include <iostream>
#include <string>

export module inh_poly_1;

namespace inh_poly_1 {
    export class Person {
        friend std::ostream &operator<<(std::ostream &out, const Person &person);

    public:
        Person() = default;
        Person(const std::string &first_name_param, const std::string &last_name_param);
        ~Person() = default;

        // Getters
        std::string get_first_name() const { return m_first_name; }
        std::string get_last_name() const { return m_last_name; }

        // Setters
        void set_first_name(std::string_view fn) { m_first_name = fn; }
        void set_last_name(std::string_view ln) { m_last_name = ln; }

    private:
        std::string m_first_name{ "Mysterious" };
        std::string m_last_name{ "Person" };
    };

    // Implementations
    Person::Person(const std::string &first_name_param, const std::string &last_name_param)
        : m_first_name(first_name_param), m_last_name(last_name_param) {}

    export std::ostream &operator<<(std::ostream &out, const Person &person) {
        out << "Person [" << person.m_first_name << " " << person.m_last_name << "]";
        return out;
    }

    //The Player class
    export class Player : public Person {
        friend std::ostream &operator<<(std::ostream &out, const Player &player);

    public:
        Player() = default;
        explicit Player(std::string_view game_param);

    private:
        std::string m_game{ "None" };
    };

    // Implementations
    Player::Player(std::string_view game_param) : m_game(game_param) {}

    export std::ostream &operator<<(std::ostream &out, const Player &player) {
        out << "Player : [ game: " << player.m_game << " names: " << player.get_first_name() << " "
            << player.get_last_name() << "]";
        return out;
    }
} // namespace inh_poly_1