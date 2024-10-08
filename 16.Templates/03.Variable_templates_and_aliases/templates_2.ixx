/*
    . Exploring alias templates: 
        . A way to provide a new name for an existing type.
        . Syntax: 
            . template <typename T> using NewName = ExistingType<T>;
*/
module;

#include <vector>
#include <string>
#include <map>

export module templates_2;

namespace templates_2{

    // KeyValueStore class template 
    export template <typename Key, typename Value>
    class KeyValueStore {
    public:
        void insert(const Key& key, const Value& value) {
            store[key] = value;
        }

        Value get(const Key& key) const {
            return store.at(key);
        }

    private:
        std::map<Key, Value> store;
    };

    //using declarations
    // Alias template for std::vector<T>
    export template <typename T>
    using Vec = std::vector<T>;

    // Alias template for KeyValueStore with std::string as key
    export template <typename Value>
    using StringKeyStore = KeyValueStore<std::string, Value>;
    
} // namespace templates_2