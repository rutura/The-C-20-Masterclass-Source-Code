/*
    . Exploring the need for exceptions
        . Problem: integer division by zero
        . Problem: Downcast troubles
        . Exceptions: recover from division by zero
        . Exceptions: recover from bad downcast
        . Exceptions coming from elsewhere
*/
module;

#include <fmt/format.h>
#include <string>
#include <typeinfo>

export module exceptions_2;

namespace exceptions_2{

    export class Animal {
    public:
        Animal() = default;
        virtual void breathe() const {};
        virtual ~Animal() = default;
    private:
        std::string m_description;
    };

    export class Dog : public Animal {
    public:
        Dog() = default;
        virtual void breathe() const override {};
        void run() { fmt::println("Dog running..."); }
        virtual ~Dog() override = default;
    private:
        std::string m_fur_color;
    };

    /* Function throws const char* exception when par_b is zero */
    export void process_parameters(int par_a, int par_b) {
        // Do some processing
        if (par_b == 0) throw "Potential division by 0 detected"; // Throwing a const char* exception

        int result = par_a / par_b;

        // Some other processing.
    }


    //Helper methods
    export void integer_division_by_zero(){
        // int division by 0 : CRASH
        const int a{45};
        const int b{0};
        //int result = a/b;		//Some compilers flag division by zero as an error out of the box.
        fmt::println( "Done!" );
    }

    export void downcast_troubles(){
        // Downcast using dynamic_cast with references
        // The hierarchy of Animal->Dog has to be polymorphic to be able to do
        // this. This throws an exception because animal has no dog part so the
        // cast won't really work.
        Animal a;
        Dog& d{dynamic_cast<Dog&>(a)};
        fmt::println( "Done!" );
    }


    export void recover_from_division_by_zero(){
        // Exceptions allow us to recover from these errors and give
        // our program a chance to continue running.
        // Integer division
        // If we throw int, and there is no catch block for int, the program will still crash
        // We can have more than one catch block for different types of exceptions. Here we have int and std::string
        const int a{45};
        const int b{0};
        int result;

        try{
            if(b == 0)
            throw 0;
            //result = a/b;	//Some compilers flag division by zero as an error out of the box.
        }catch(std::string ex){
            //Some processing
            fmt::println( "Something went wrong : {}", ex );
        }
        catch(int ex){
            fmt::println( "Integer division detected, ex  : {}", ex );
        }
        fmt::println("Done." );
    }

    export void recover_from_bad_downcast(){

        // Downcast using dynamic_cast with references
        // The hierarchy of Animal->Dog has to be polymorphic to be able to do
        // this. This throws an exception because animal has no dog part so the
        // cast won't really work.
        Animal a;
        try{
            Dog& d{dynamic_cast<Dog&>(a)};
        }catch(std::bad_cast ex){
            fmt::println( "Something went wrong : {}", ex.what() );
        }
        fmt::println( "Done!" );
    }

    export void exceptions_coming_from_elsewhere(){
        // Exceptions thrown out of other parts of code written by you
        // or somebody else
        try {
            process_parameters(10, 0);
        } catch (const char *ex) {
            fmt::println("Exception: {}", ex);
        }

        fmt::println("Done!");
    }
    
} // namespace exceptions_2