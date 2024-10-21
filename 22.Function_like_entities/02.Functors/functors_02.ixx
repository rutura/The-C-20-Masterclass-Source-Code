/*
        .#2: Standard functors
*/
module;

export module functors_02;

import box_container_it_5;

using iteration_5::BoxContainer;

namespace functors_02 {

    export template<typename T, typename Comparator>
    T get_best(const BoxContainer<T> &collection, Comparator comparator) {
        T best = collection.get_item(0);
        for (size_t i{}; i < collection.size(); ++i) {
            if (comparator(collection.get_item(i), best)) {
                best = collection.get_item(i);
            }
        }
        return best;
    }

    // Custom function
    export template<typename T>
    bool custom_greater(const T &param1, const T &param2) {
        return param1 > param2;
    }

    // Custom functor
    export template<typename T>
    class Greater {
    public:
        bool operator()(const T &param1, const T &param2) {
            return param1 > param2;
        }
    };

} // namespace functors_02
