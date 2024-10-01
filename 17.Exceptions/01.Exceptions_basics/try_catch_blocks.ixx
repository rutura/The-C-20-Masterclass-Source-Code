module;

#include <fmt/format.h>

export module try_catch_blocks;

namespace try_catch_blocks{

    export class Item
    {
    public:
    Item() { fmt::println("Item constructor called"); }

    ~Item() { fmt::println("Item destructor called"); }
    };

    export class MyException
    {
    public:
    MyException() = default;

    // MyException(const MyException & ex) = delete;
    public:
    MyException(const MyException &ex) {}
    };

}   // namespace try_catch_blocks