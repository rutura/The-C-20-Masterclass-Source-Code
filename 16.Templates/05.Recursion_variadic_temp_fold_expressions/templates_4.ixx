/*
    . Fold expressions: 
        .  fold expressions allow you to apply a binary operator to a parameter pack, expanding it 
            in various ways depending on the type of fold expression.
        . We have two forms: 
            . Unary fold expressions, which don't have an initial value.
            . Binary fold expressions, which have an initial value.

        . Diving deep into each: 
            . 1. Unary Fold Expressions
                . No Initial Value: Unary fold expressions operate only on the arguments provided in 
                  the parameter pack, without an extra initial value.
                    . Types:
                        . Unary Left Fold: ( ... op args)
                            . Applies the operator from left to right.
                            . Example: (1 + 2 + 3) becomes ((1 + 2) + 3)
                        . Unary Right Fold: (args op ...)
                            . Applies the operator from right to left.
                            . Example: (1 + 2 + 3) becomes (1 + (2 + 3))

            . 2. Binary Fold Expressions
                . With Initial Value: Binary fold expressions use an initial value in addition to the parameter pack. This value serves as a starting point for the fold operation.
                    . Types:
                        . Binary Left Fold: (init op ... op args)
                            . Applies the operator from left to right, but starts with an initial value.
                            . Example: 0 + (1 + 2 + 3) becomes 0 + ((1 + 2) + 3)
                        . Binary Right Fold: (args op ... op init)
                            . Applies the operator from right to left, ending with the initial value.
                            . Example: (1 + 2 + 3) + 0 becomes (1 + (2 + (3 + 0)))
        . Breaking down unary left fold when called with add(1,2,3,4,5)
            1. Template Instantiation:
                . The compiler sees that you're calling add_unary_left_fold with 5 arguments: 1, 2, 3, 4, 5.

            2. Fold Expression:
                . The fold expression ( ... + args) is what we call a unary left fold.
                . This means the + operator will be applied to the values starting from the left, like this:
                    . (((1 + 2) + 3) + 4) + 5
            3. Visual representation: 
                Start:             1 + 2 + 3 + 4 + 5
                First operation:   (1 + 2) + 3 + 4 + 5  =>  3 + 3 + 4 + 5
                Second operation:  (3 + 3) + 4 + 5      =>  6 + 4 + 5
                Third operation:   (6 + 4) + 5          =>  10 + 5
                Final operation:   10 + 5               =>  15
            4. Birds'eye view: 
                . The compiler takes the argument pack (1, 2, 3, 4, 5) and matches it with the template parameter Args....
                . It then performs a left fold, applying the + operator starting from the leftmost element (1).
                . The compiler repeatedly adds the values one by one, always taking the result of the previous addition and combining it with the next number in the pack.
                . The final result after adding all the numbers is 15.
        . Comparisons: 
                | Aspect            | Unary Left       | Unary Right      | Binary Left       | Binary Right          |
                |-------------------|------------------|------------------|-------------------|-----------------------|
                | Syntax            | (... op args)    | (args op ...)    | (init op ...)     | (args op ... op init) |
                | Direction         | Left             | Right            | Left              | Right                 |
                | Example           | ((1 + 2) + 3)    | (1 + (2 + 3))    | 0 + ((1 + 2) + 3) | (1 + (2 + (3 + 0)))   |
                | No Args           | No (error)       | No (error)       | Yes               | Yes                   |
                | Initial Value     | None             | None             | Required          | Required              |

 */
module;

export module templates_4;

namespace templates_4{

    // Unary left fold: (1,2,3) becomes ((1 + 2) + 3)
    export template <typename... Args>
    auto add_unary_left_fold(Args... args) {
        return ( ... + args);
    }

    //  Unary right fold; (1,2,3) becomes (1 + (2 + 3))
    export template <typename... Args>
    auto add_unary_right_fold(Args... args) {
        return (args + ...);
    }

    //  Binary left fold: (1,2,3) becomes 0 + (1 + (2 + 3))
    export template <typename... Args>
    auto add_binary_left_fold(Args... args) {
        return (0 + ... + args);
    }

    //  Binary right fold; (1,2,3) becomes ((1 + (2 + 3)) + 0)
    export template <typename... Args>
    auto add_binary_right_fold(Args... args) {
        return (args + ... + 0);
    }

    
} // namespace templates_4