/*
    Exploring  sequence containers, the iterators they provide and
    common algorithms that require these iterators.

        . std::vector: 
            . Iterator type: random access iterator
            . Common algorithms: std::sort, std::reverse and std::find
                . std::sort requires random access iterators because it relies on fast access to elements for comparisons and swapping.
                . std::reverse uses bidirectional iterators, which random access iterators satisfy.
                . std::find works with input iterators, and random access iterators meet this requirement.

        . std::list:
            . Iterator type: bidirectional iterator
            . Common algorithms: std::remove, std::unique and std::reverse
                . std::remove works with forward iterators, and bidirectional iterators meet this requirement.
                . std::unique requires forward iterators and is useful for eliminating consecutive duplicates.
                . std::reverse necessitates bidirectional iterators, as it swaps elements from both ends of the container.

        . std::deque
            . Iterators Provided: Random access iterators.
            . Common Algorithms: std::sort, std::reverse, std::rotate.
                . std::sort requires random access iterators, which std::deque provides.
                . std::reverse works with bidirectional iterators, and std::deque meets this requirement.
                . std::rotate also works with forward iterators, and std::deque's random access iterators suffice.

        . std::forward_list
            . Iterators Provided: Forward iterators.
            . Common Algorithms: std::remove, std::unique, std::merge.
                . std::remove requires forward iterators, which std::forward_list provides.
                . std::unique works with forward iterators, useful for eliminating consecutive duplicates.
                . std::merge requires sorted ranges and forward iterators to efficiently combine two lists.

        . std::array
            . Iterators Provided: Random access iterators.
            . Common Algorithms: std::sort, std::copy, std::reverse.
                . std::sort works with random access iterators, which std::array provides.
                . std::copy works with input and output iterators, and random access iterators are sufficient.
                . std::reverse requires bidirectional iterators, and random access iterators suffice.
*/
module;

#include <vector>
#include <deque>
#include <algorithm>
#include <concepts>
#include <ranges>
#include <list>
#include <forward_list>
#include <fmt/format.h>

export module containers_iterators_algorithms_01;

namespace containers_iterators_algorithms_01{


    //A function template to print any container
    /*
    template<typename Container>
    void print_container(const Container& container){
        for (const auto& elem : container){
            fmt::print("{} ", elem);
        }
        fmt::print("\n");
    }
    */

   // We clearly communicate that the function requires an input range: that is, 
   // a range that can be iterated over in a forward direction.
    export template<std::ranges::input_range Container>
    void print_container(const Container& container) {
        for (const auto& elem : container) {
            fmt::print("{} ", elem);
        }
        fmt::print("\n");
    }


    //std::vector: iterator type: random access iterator, common algorithms: std::sort, std::reverse and std::find
    export void use_vector(){
        fmt::print("Vector operations\n");

        std::vector<int> vec = {5, 3, 8, 1, 2};
        print_container(vec);

        // Sort the vector: from smallest to largest by default
        std::sort(std::begin(vec), std::end(vec));
        print_container(vec);
        

        // Reverse the vector
        std::reverse(std::begin(vec), std::end(vec));
        print_container(vec);

        // Find an element
        auto it = std::find(std::begin(vec), std::end(vec), 8);

        if (it != std::end(vec)) {
            fmt::println("Found: {}", *it);
        } else {
            fmt::println("Not Found");
        }

        //Sort the vector in descending order
        std::sort(std::begin(vec), std::end(vec), std::greater<int>());
        print_container(vec);

        //Sort the vector in ascending order, through a lambda as a comparator
        std::sort(std::begin(vec), std::end(vec), [](int a, int b){return a < b;});
        print_container(vec);
    }

    export void use_list(){
        //Here we use member algorithms.
        fmt::print("List operations\n");

        std::list<int> lst = {1,1, 2, 3, 4, 3, 5, 2};
        print_container(lst);

        // Remove elements with value 3
        //lst.remove(3);
        print_container(lst);

        // Remove consecutive duplicates
        lst.unique();
        print_container(lst);

        // Reverse the list
        lst.reverse();
        print_container(lst);

    }

    export void use_deque(){
        fmt::print("Deque operations\n");

        std::deque<int> deq = {5, 3, 8, 1, 2};
        print_container(deq);

        // Sort the deque: from smallest to largest by default
        std::sort(std::begin(deq), std::end(deq));
        print_container(deq);

        // Reverse the deque
        std::reverse(std::begin(deq), std::end(deq));
        print_container(deq);

        // Rotate the deque
        std::rotate(std::begin(deq), std::begin(deq) + 1, std::end(deq));
        print_container(deq);
    }

    export void use_forward_list(){
        fmt::print("Forward list operations\n");

        std::forward_list<int> flst = {5, 3, 8, 1, 2};
        print_container(flst);

        // Remove elements with value 3
        flst.remove(3);
        print_container(flst);

        // Remove consecutive duplicates
        flst.unique();
        print_container(flst);

        // Merge two sorted lists
        std::forward_list<int> flst2 = {4, 6, 7};
        flst.merge(flst2);
        print_container(flst);
    }

}   // namespace containers_iterators_algorithms_01