/*
    . Exploring protected members: 
        . It is used limit access to child classes.
        . Protected members are only accessible to the child classes.
        . They aren't accessible to the outside world.
*/
module;

#include <iostream>
#include <string>

export module inh_poly_2;

namespace inh_poly_2{

    // Person class
    export class Person {
        friend std::ostream &operator<<(std::ostream &out, const Person &person);

    public:
        Person();
        Person(const std::string &first_name_param, const std::string &last_name_param);
        ~Person();

        // Getters
        std::string get_first_name() const { return m_first_name; }
        std::string get_last_name() const { return m_last_name; }

        // Setters
        void set_first_name(std::string_view fn) { m_first_name = fn; }
        void set_last_name(std::string_view ln) { m_last_name = ln; }

    protected:
        std::string m_first_name{ "Mysterious" };
        std::string m_last_name{ "Person" };
    };

    // Implementations
    Person::Person() {}

    Person::Person(const std::string &first_name_param, const std::string &last_name_param)
        : m_first_name(first_name_param), m_last_name(last_name_param) {}

    export std::ostream &operator<<(std::ostream &out, const Person &person) {
        out << "Person [" << person.m_first_name << " " << person.m_last_name << "]";
        return out;
    }

    Person::~Person() {}

    // Player class
    export class Player : public Person {
        friend std::ostream &operator<<(std::ostream &out, const Player &player);

    public:
        Player() = default;
        Player(std::string_view game_param, std::string_view first_name_param, std::string_view last_name_param);

    private:
        std::string m_game{ "None" };
    };

    // Implementations
    Player::Player(std::string_view game_param, std::string_view first_name_param, std::string_view last_name_param) {
        m_game = game_param;
        m_first_name = first_name_param;
        m_last_name = last_name_param;
    }

    export std::ostream &operator<<(std::ostream &out, const Player &player) {
        out << "Player: [ game: " << player.m_game << " names: " << player.get_first_name() << " "
            << player.get_last_name() << "]";
        return out;
    }
    
} // namespace inh_poly_2