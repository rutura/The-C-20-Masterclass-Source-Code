module;

#include <string>
#include <iostream>
#include <string_view>

export module inh_basics;

namespace inh_basics{

    export class Person
    {
    friend std::ostream &operator<<(std::ostream &out, const Person &person);

    public:
    Person();
    Person(std::string &first_name_param, std::string &last_name_param);
    ~Person();

    // Getters
    std::string get_first_name() const { return first_name; }

    std::string get_last_name() const { return last_name; }

    // Setters
    void set_first_name(std::string_view fn) { first_name = fn; }
    void set_last_name(std::string_view ln) { last_name = ln; }

    private:
    std::string first_name{ "Mysterious" };
    std::string last_name{ "Person" };
    };

    //Implementations
    Person::Person() {}

    Person::Person(std::string &first_name_param, std::string &last_name_param)
    : first_name(first_name_param), last_name(last_name_param)
    {}

    export std::ostream &operator<<(std::ostream &out, const Person &person)
    {
    out << "Person [" << person.first_name << " " << person.last_name << "]";
    return out;
    }

    Person::~Person() {}

    //Player

    export class Player : public Person
    {
    friend std::ostream &operator<<(std::ostream &out, const Player &player);

    public:
    Player() = default;
    Player(std::string_view game_param);

    private:
    std::string m_game{ "None" };
    };

    //Implementations

    Player::Player(std::string_view game_param) : m_game(game_param)
    {
    // first_name = "John"; Compiler errors
    // last_name = "Snow";
    }

    export std::ostream &operator<<(std::ostream &out, const Player &player)
    {

    out << "Player : [ game : " << player.m_game << " names : " << player.get_first_name() << " "
        << player.get_last_name() << "]";
    return out;
    }

}   