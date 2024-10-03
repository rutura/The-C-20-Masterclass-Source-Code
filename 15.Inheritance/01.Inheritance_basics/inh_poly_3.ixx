/*
    . Exploring base class access specifiers: 
        . public inheritance
        . protected inheritance
        . private inheritance
*/
module;

#include <iostream>
#include <string>

export module inh_poly_3;

namespace inh_poly_3 {

    // Person
    export class Person {
        friend std::ostream &operator<<(std::ostream &, const Person &person);

    public:
        Person() = default;
        Person(const std::string &fullname, int age, const std::string &address);

        // Getters
        std::string get_full_name() const { return m_full_name; }
        int get_age() const { return m_age; }
        std::string get_address() const { return m_address; }

        // Setters
        void set_full_name(std::string_view fullname) { m_full_name = fullname; }
        void set_age(int age) { m_age = age; }
        void set_address(std::string_view address) { m_address = address; }

    public:
        std::string m_full_name{ "None" };

    protected:
        int m_age{ 0 };

    private:
        std::string m_address{ "None" };
    };

    // Implementation
    Person::Person(const std::string &fullname, int age, const std::string &address)
        : m_full_name{ fullname }, m_age{ age }, m_address{ address } {}

    export std::ostream &operator<<(std::ostream &out, const Person &person) {
        out << "Person [Full name :" << person.get_full_name() << ", Age:" << person.get_age()
            << ", Address:" << person.get_address() << "]";
        return out;
    }

    // Player class
    export class Player : public Person {
        friend std::ostream &operator<<(std::ostream &out, const Player &player);

    public:
        Player();

        // See the access we have to inherited members from Person
        void play() {
            m_full_name = "John Snow"; // OK
            m_age = 55;                // OK
            // m_address = "DSAKFD;ASKFJ;DKAS"; Compiler error
        }

    private:
        int m_career_start_year{ 0 };
        double m_salary{ 0.0 };
        int m_health_factor{ 0 }; // Let's say that it's 0~10
    };

    // Implementations
    Player::Player() {}

    export std::ostream &operator<<(std::ostream &out, const Player &player) {
        out << "Player[Full name : " << player.get_full_name() << ",age : " << player.get_age()
            << ",address : " << player.get_address() << "]";
        return out;
    }

    // Nurse class
    export class Nurse : protected Person {
        friend std::ostream &operator<<(std::ostream &, const Nurse &operand);

    public:
        Nurse() = default;

        void treat_unwell_person() {
            m_full_name = "John Snow"; // OK
            m_age = 23;                // OK
            // m_address = "897-78-723"; Compiler error
        }

    private:
        int m_practice_certificate_id{ 0 };
    };

    // Implementation
    export std::ostream &operator<<(std::ostream &out, const Nurse &operand) {
        out << "Nurse [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
            << ",address : " << operand.get_address() << ",practice certificate id : " << operand.m_practice_certificate_id
            << "]";
        return out;
    }

    // Engineer class
    export class Engineer : private Person {
        friend std::ostream &operator<<(std::ostream &out, const Engineer &operand);

    public:
        Engineer() = default;

        void build_something() {
            m_full_name = "John Snow"; // OK
            m_age = 23;                // OK
            // m_address = "897-78-723"; Compiler error
        }

    private:
        int m_contract_count{ 0 };
    };

    // Implementation
    export std::ostream &operator<<(std::ostream &out, const Engineer &operand) {
        out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
            << ",address : " << operand.get_address() << ",contract_count : " << operand.m_contract_count << "]";
        return out;
    }

} // namespace inh_poly_3