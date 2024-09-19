/*
    . Fold expressions: 
        . We have two forms: 
            . Unary fold expressions, which don't have an initial value.
            . Binary fold expressions, which have an initial value.
 */
#pragma once

namespace fold_expressions {

// Unary left fold
// add(1,2,3) becomes ((1 + 2) + 3)
template<typename... Args> auto add_unary_left_fold(Args... args) { return ( ... + args); }

//sub(1,2,3) becomes ((1 - 2) - 3)
template<typename... Args> auto sub_unary_left_fold(Args... args) { return ( ... - args); }

/************************************************************* */

//  Unary right fold
// add(1,2,3) becomes (1 + (2 + 3))
template<typename... Args> auto add_unary_right_fold(Args... args) { return (args + ...); }

//sub(1,2,3) becomes (1 - (2 - 3))
template<typename... Args> auto sub_unary_right_fold(Args... args) { return (args - ...); }

/************************************************************* */

//  Binary left fold
// add(1,2,3) becomes 0 + (1 + (2 + 3))
template<typename... Args> auto add_binary_left_fold(Args... args) { return (0 + ... + args); }

//sub(1,2,3) becomes 0 - (1 - (2 - 3))
template<typename... Args> auto sub_binary_left_fold(Args... args) { return (0 - ... - args); }

/************************************************************* */

//  Binary right fold
// add(1,2,3) becomes ((1 + (2 + 3)) + 0)
template<typename... Args> auto add_binary_right_fold(Args... args) { return (args + ... + 0); }

//Function sub_binary_right_fold
//sub(1,2,3) becomes ((1 - (2 - 3)) - 0)
template<typename... Args> auto sub_binary_right_fold(Args... args) { return (args - ... - 0); }

}// namespace fold_expressions