#include <print>

import forecast;                   // the whole module: model and stats, not detail

int main() {
    Series north{{{6, 11.5}, {12, 18.5}, {18, 15.0}, {24, 12.0}}};

    std::println("north: mean {:.2f}, spread {:.2f}", mean_of(north), spread_of(north));

    // Importers see the module, never its partitions. These do not compile:
    //
    //     import forecast:model;                      // a partition can only be imported inside its own module
    //     std::println("{}", square(3.0));            // detail is internal: square() does not exist here
    return 0;
}
