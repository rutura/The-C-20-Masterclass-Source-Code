/*
    . Exploring exceptions in destructors: 
        . Exceptions in destructors are a bad idea.
        . Destructors are are noexcept by default.
        . If an exception is thrown in a destructor, the program will terminate.
        . The reason is that the destructor is called as part of the stack unwinding process.
        . If an exception is thrown during stack unwinding, the program will terminate.

    . Note: You can allow exceptions to be thrown from destructors by using the noexcept(false) specifier.
        . This is not recommended. DON'T DO IT.
*/
module;

export module exceptions_5;

namespace exceptions_5{

    export class Item
    {
    public:
        Item() {}
        //~Item() noexcept(false)
        //~Item() noexcept
        ~Item()
        {
            //Uncomment the code below to show how bad it is to throw exceptions in destructors.
            /*
            try {
                throw 0;
            } catch (int ex) {
                throw;
            }
            */
        }
    };
    
} // namespace exceptions_5
