#include <print>
#include <stdexcept>
#include <vector>

void print_stock(const std::vector<int>& stock) {
    for (const int& quantity : stock) {
        std::print("{} ", quantity);
    }
    std::println("");
}

int main() {

    // std::vector<T> - like std::array, but its size can change at run
    // time and its elements live on the heap. This is what std::array
    // cannot do: push_back appends one element, resizing as needed.
    std::vector<int> warehouse_stock;   // starts empty, size() == 0
    std::println("New warehouse: size is {}", warehouse_stock.size());

    warehouse_stock.push_back(40);
    warehouse_stock.push_back(15);
    warehouse_stock.push_back(60);
    std::println("After three deliveries: size is {}", warehouse_stock.size());
    std::print("warehouse_stock: ");
    print_stock(warehouse_stock);

    // vector(N) makes N elements, each value-initialized to 0 - a
    // different way to build one than growing it with push_back.
    std::vector<int> storefront_stock(5);
    std::vector<int> backroom_stock(8);

    std::println("\nSize of storefront_stock is {}", storefront_stock.size());
    print_stock(storefront_stock);

    std::println("Size of backroom_stock is {}", backroom_stock.size());
    print_stock(backroom_stock);

    // Two vectors compare element by element, like std::array.
    if (storefront_stock != backroom_stock) {
        std::println("storefront_stock and backroom_stock are not equal "
                      "(different sizes)");
    }

    // Copy constructor: overflow_stock starts as an independent copy.
    std::vector overflow_stock{backroom_stock};
    std::println("\nSize of overflow_stock is {}", overflow_stock.size());

    // Assignment replaces storefront_stock's contents with backroom_stock's.
    storefront_stock = backroom_stock;
    std::println("\nAfter assigning backroom_stock to storefront_stock:");
    std::println("storefront_stock and backroom_stock are equal: {}",
                  storefront_stock == backroom_stock);

    // .at(i) as an lvalue: bounds-checked write.
    storefront_stock.at(3) = 250;
    std::print("storefront_stock: ");
    print_stock(storefront_stock);

    // Out-of-range access throws std::out_of_range - catch it instead of
    // crashing.
    try {
        std::println("\nAttempting storefront_stock.at(20)");
        std::println("{}", storefront_stock.at(20));
    }
    catch (const std::out_of_range& ex) {
        std::println("An exception occurred: {}", ex.what());
    }

    return 0;
}
