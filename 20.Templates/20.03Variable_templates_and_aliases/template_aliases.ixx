module;

#include <vector>
#include <string>
#include <map>

export module template_aliases;

namespace template_aliases{

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

}   // namespace template_aliases