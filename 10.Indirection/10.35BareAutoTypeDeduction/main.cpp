#include <print>

int main() {

    // Bare auto deduction: just a copy
    /*
    double some_var{55.5};
    auto x = some_var;

    std::println("sizeof(some_var) : {}", sizeof(some_var));
    std::println("sizeof(x) : {}", sizeof(x));
    std::println("&some_var : {}", static_cast<const void*>(&some_var));
    std::println("&x : {}", static_cast<const void*>(&x));
    std::println("some_var : {}", some_var);
    std::println("x : {}", x);
    */

    // auto (no &) never deduces a reference, even when initialized from
    // one - x/y here are always independent copies.
    /*
    double some_var = 55.5;
    double& some_var_ref{some_var};

    auto y = some_var_ref; // y is not a reference - just a double holding
                            // whatever value some_var_ref currently has
    ++y;

    std::println("sizeof(some_var) : {}", sizeof(some_var));     // 8
    std::println("sizeof(some_var_ref) : {}", sizeof(some_var_ref)); // 8
    std::println("sizeof(y) : {}", sizeof(y));                   // 8
    std::println("&some_var : {}", static_cast<const void*>(&some_var));
    std::println("&some_var_ref : {}", static_cast<const void*>(&some_var_ref)); // same as &some_var
    std::println("&y : {}", static_cast<const void*>(&y));       // different address
    std::println("some_var : {}", some_var);         // 55.5
    std::println("some_var_ref : {}", some_var_ref); // 55.5
    std::println("y : {}", y);                        // 56.5
    */

    // auto& (with the &) does deduce a real reference.
    /*
    double some_var = 55.5;
    double& some_var_ref{some_var};

    auto& z = some_var_ref; // z is deduced as double&
    ++z;

    std::println("sizeof(z) : {}", sizeof(z)); // 8
    std::println("&some_var : {}", static_cast<const void*>(&some_var));
    std::println("&some_var_ref : {}", static_cast<const void*>(&some_var_ref));
    std::println("&z : {}", static_cast<const void*>(&z)); // same address as some_var
    std::println("some_var : {}", some_var);         // 56.5
    std::println("some_var_ref : {}", some_var_ref); // 56.5
    std::println("z : {}", z);                        // 56.5
    */

    // Constness is preserved when auto& deduces a real reference.
    /*
    const double some_other_var{44.3};
    const double& const_ref{some_other_var};
    auto& p = const_ref; // p is deduced as const double&

    std::println("some_other_var : {}", some_other_var);
    std::println("const_ref : {}", const_ref);
    std::println("p : {}", p);

    // ++p; // compiler error: p is a reference to const

    std::println("some_other_var : {}", some_other_var);
    */

    // Constness doesn't carry over to a bare (non-reference) auto - the
    // copy is a brand new, independently-modifiable variable.
    const double i_am_const{71.2};
    const double& my_ref{i_am_const};

    auto q = my_ref; // q is a separate variable, initialized from i_am_const's value
    ++q;              // fine - q is just a double, not const

    std::println("i_am_const : {}", i_am_const);
    std::println("my_ref : {}", my_ref);
    std::println("q : {}", q);

    return 0;
}
