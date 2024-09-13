module;

export module exceptions_in_destructors;

namespace exceptions_in_destructors{

    export class Item
    {
    public:
    Item() {}
    ~Item()
    {
        try {
        throw 0;
        } catch (int ex) {
        throw;
        }
    }
    };

}   // namespace exceptions_in_destructors