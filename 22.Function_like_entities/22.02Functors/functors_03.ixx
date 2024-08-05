module;

#include <concepts>

export module functors_03;

import boxcontainer;

namespace functors_03{

    // A functor can  take parameters and internally
    //  store them as member variables
    export template<typename T> 
    requires std::is_arithmetic_v<T> 
    class IsInRange
    {
    public:
    IsInRange(T min, T max) : min_inclusive{ min }, max_inclusive{ max } {}
    bool operator()(T value) const { return ((value >= min_inclusive) && (value <= max_inclusive)); }

    private:
    T min_inclusive;
    T max_inclusive;
    };


    export template<typename T, typename RangePicker>
    requires std::is_arithmetic_v<T> 
    T range_sum(const box::BoxContainer<T> &collection, RangePicker is_in_range)
    {

    T sum{};
    for (size_t i{}; i < collection.size(); ++i) {
        if (is_in_range(collection.get_item(i))) sum += collection.get_item(i);
    }
    return sum;
    }

}   // namespace functors_03