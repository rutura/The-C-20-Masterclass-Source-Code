/*
    . Compiler generated constructor summary: 
        1. You have no constructors in your class.
            . The compiler generates: 
                . Default constructor. You can do something like Pixel p;
                . Copy constructor. You caqn do something like Pixel p1 = p2;
            . Things you can do: 
                                Pixel a;          // Default constructor
                                Pixel b{a};       // Copy constructor

        2. You have a default constructor only: 
            . The compiler generates: 
                . Copy constructor. You can do something like Pixel p1 = p2;
            . Things you can do: 
                                Pixel a;          // Default constructor
                                Pixel b{a};       // Copy constructor

        3. You have a copy constructor only: 
            . The compiler generates: 
                . No other constructors. You can't create other objects without making copies, 
                . But you can't create an object to copy from in the first, place, so you can't create anything
            . Things you can do: 
                                Pixel b{a};       // Copy constructor (if 'Pixel a' exists)

        4. You have a single or multi-argement non-copy constructor: 
            . The compiler generates: 
                . Copy constructor. You can do something like Pixel p1 = p2;
            . Things you can do: 
                                Pixel a{0xFF000000};  // Constructor with arguments
                                Pixel b{a};

        5. You have a default constructor, and a single or multi-argement non-copy constructor: 
            . The compiler generates: 
                . Copy constructor. You can do something like Pixel p1 = p2;
            . Things you can do: 
                                Pixel a;              // Default constructor
                                Pixel b{0xFF000000};  // Constructor with arguments
                                Pixel c{a};           // Copy constructor
*/
module;


export module ct12;

