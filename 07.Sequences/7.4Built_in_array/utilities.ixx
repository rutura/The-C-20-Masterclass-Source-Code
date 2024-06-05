module;
#include <string_view>
#include <fmt/format.h>
#include <string>
#include <ctime>
#include <random>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::print("{}\n", msg);
}

export void declaration_and_initialization(){

    // Declare an array of ints
    // int scores [10]; // Junk data

    // Read data

    // fmt::println( " scores [0] : {}",  scores[0] );
    // fmt::println( " scores [1] : {}",  scores[1] );


    // Read with a loop
    /*
    for( size_t i {0} ; i < 10 ; ++i){
        fmt::println("scores [{}] : {}", i, scores[i] );
    }
    */


    /*
    scores[0] = 20;
    scores[1] = 21;
    scores[2] = 22;

    //Print the data out
    for( size_t i {0} ; i < 10 ; ++i){
        fmt::println("scores [{}] : {}", i, scores[i] );

    }
    */


    // Write data in a loop
    /*
    for(size_t i{0}; i < 10 ; ++i){
        scores[i] = i * 10;
    }

    //Print the data out
    for( size_t i {0} ; i < 10 ; ++i){
        fmt::println("scores [{}] : {}", i, scores[i] );


    }
    */

    // Declare and initialize at the same time
    /*
        double salaries[5] {12.7, 7.5, 13.2, 8.1, 9.3};

        for(size_t i{0}; i < 5; ++i){
        fmt::println("salaries [{}] : {}", i, salaries[i] );
    ;
        }
    */


    // If you don't initialize all the elements, those you leave out
    // are initialized to 0
    /*
    int families[5] {12, 7, 5};

        for(size_t i{0}; i < 5; ++i){
        fmt::println("families [{}] : {}", i, families[i] );

        }
    */


    // Omit the size of the array at declaration
    /*
    int class_sizes[] {10,12,15,11,18,17,23,56};

        // Will print this with a range based for loop
        for(auto value : class_sizes){
                fmt::println("value : {}", value);
        }
    */


    // Read only arrays
    /*
    const int birds[] {10,12,15,11,18,17,23,56};
    birds[2] = 8;
    */


    // Sum up scores array, store result in sum

    int scores[]{ 2, 5, 8, 2, 5, 6, 9 };
    int sum{ 0 };

    for (int element : scores) { sum += element; }
    fmt::println("Score sum : {}", sum);
}

export void size_of_an_array(){

    int scores[]{ 1, 2, 5 };


    int count{ std::size(scores) };// std::size( C++17)

    fmt::println("sizeof(scores) : {}", sizeof(scores));
    fmt::println("sizeof(scores[0]) : {}", sizeof(scores[0]));
    fmt::println("count : {}", count);


    /*
    int count {sizeof(scores)/sizeof(scores[0])};


    for(size_t i {0} ; i < count ; ++i){
        fmt::println( "scores [{}] : {}",i , scores[i] );
    }


    //Range based for loop
    for ( auto i : scores){
            fmt::println( "value  : {}" , i );
    }
    */
}

export void array_of_characters(){

    // Declare array
    char message[5]{ 'H', 'e', 'l', 'l', 'o' };
    // int data[5] {1,2,3,3,3};

    // fmt::println( "data : {}",  data );


    // Print out the array through looping
    /*
    fmt::println( "message : ");
    for( auto c : message){
        fmt::println( c );
    }
    */


    /*
    //Change characters in our array
    message[1] = 'a';

    //Print out the array through looping
    fmt::println( "message : ");
    for( auto c : message){
        fmt::println( c );
    }
    */


    // Will probably print garbage after your char array
    /*
    fmt::println( "message : {}", message );
    */


    // If a character array is null terminated, it's called as C-String
    /*
    char message1 [] {'H','e','l','l','o','\0'};
    fmt::println( "message1 : {}", message1 );
    fmt::println( "sizeof(message1) : {}", sizeof(message1) );
    */


    /*
    char message2 [6] {'H','e','l','l','o'};
    fmt::println( "message2 : {}", message2 );
    fmt::println( "sizeof(message2) : {}", sizeof(message2) );

    char message3 [] {'H','e','l','l','o'}; // This is not a c string ,
                                                                                        //as there is not null character
    fmt::println( "message3 : {}", message3 );
    fmt::println( "sizeof(message3) : {}", sizeof(message3) );
    */


    // String literal
    char message4 [] {"Hello"};
    fmt::println( "message4 : {}", message4 );
    fmt::println( "sizeof(message4) : {}", sizeof(message4) );


    // Can't safely print out arrays other than those of characters
    /*
    int numbers[]{ 1, 2, 3, 4, 5 };
    fmt::println("numbers :  {}", numbers);// error
    */
}


export void array_bounds(){

    int numbers[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    // Read beyond bounds : Will read garbage or crash your program
    // fmt::println("numbers[12] : {}",  numbers[12]);

    // Write beyond bounds. The compiler allows it. But you don't own
    // the memory at index 12, so other programs may modify it and your
    // program may read bogus data at a later time. Or you can even
    // corrupt data used by other parts of your ptogram

    numbers[129] = 1000;
    fmt::println("numbers[129] : {}", numbers[129]);

    fmt::println("Program ending....");
}


export void random_num_old_style(){
    
    std::srand(std::time(0));// Seed

    /*
    int random_num = std::rand();

    fmt::println("random_num : {}",random_num ); // 0 ~ RAND_MAX

    random_num = std::rand();
    fmt::println("random_num : {}", random_num ); // 0 ~ RAND_MAX
    */


    // Generate random numbers in a loop
    /*
    int random_num;

    for(size_t i {0} ; i < 20 ; ++i){
        random_num = std::rand();
        fmt::println("random_num {}: {}", i,  random_num ); // 0 ~ RAND_MAX
    }
    */


    // Generate a range between 0 and 10
    /*
    int random_num =  std::rand() % 11;                  // [ 0 ~10]

    for(size_t i {0} ; i < 20 ; ++i){
        random_num = std::rand() % 11;
        fmt::println("random_num {} : {} ", i,  random_num ); // 0 ~ RAND_MAX
    }
    */


    int random_num = std::rand() % 10 + 1;// [1~10]
    for (size_t i{ 0 }; i < 20; ++i) {
        random_num = std::rand() % 10 + 1;
        fmt::println("random_num {} : {}", i, random_num);// 0 ~ RAND_MAX
    } 
}

export void random_num_modern_cplusplus(){
    //C++11
    /*
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution die{ 1, 6 };

    for (size_t count{ 0 }; count < 48; ++count) {
        fmt::println("{}", die(mersenne));
    }
    */

    // C++17
    std::random_device rd;
    std::mt19937 mersenne{ rd() };
    std::uniform_int_distribution die{ 1, 6 };

    for (size_t count{ 0 }; count < 48; ++count) {
        fmt::println("{}", die(mersenne));
    }
}

export void multi_dim_array(){
    // 2D array
    // int packages [3][4] ; // 12 locations where we can store ints

    int packages[][4]{ { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 3, 4, 5, 6 } };


    // Read data from a 2D array
    /*for (size_t i{0}; i < 3; ++i) {
        for (size_t j{0}; j < 4; ++j) {
            fmt::print("{:>2} ", packages[i][j]);
        }
        fmt::print("\n");
    }*/


    // Use std::size to query the size of array dimensions
    /*for (size_t i{0}; i < std::size(packages); ++i) {
        for (size_t j{0}; j < std::size(packages[i]); ++j) {
            fmt::print("{:>2} ", packages[i][j]);
        }
        fmt::print("\n");
    }*/


    // 3D arrays are defined in the same way. We just use three sets of indexes:
    //  3 lights per room, 5 rooms per house 7 houses per block

    int house_block[7][5][3]{
        { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 }, { 13, 14, 15 } },
        { { 16, 17, 18 }, { 19, 20, 21 }, { 22, 23, 24 }, { 25, 26, 27 }, { 28, 29, 30 } },
        { { 31, 32, 33 }, { 34, 35, 36 }, { 37, 38, 39 }, { 40, 41, 42 }, { 43, 44, 45 } },
        { { 46, 47, 48 }, { 49, 50, 51 }, { 52, 53, 54 }, { 55, 56, 57 }, { 58, 59, 60 } },
        { { 61, 62, 63 }, { 64, 65, 66 }, { 67, 68, 69 }, { 70, 71, 72 }, { 73, 74, 75 } },
        { { 76, 77, 78 }, { 79, 80, 81 }, { 82, 83, 84 }, { 85, 86, 87 }, { 88, 89, 90 } },
        { { 91, 92, 93 }, { 94, 95, 96 }, { 97, 98, 99 }, { 100, 101, 102 }, { 103, 104, 105 } } 
    };


    for (size_t i{ 0 }; i < std::size(house_block); ++i) {
        for (size_t j{ 0 }; j < std::size(house_block[i]); ++j) {
        for (size_t k{ 0 }; k < std::size(house_block[i][j]); ++k) {
            fmt::println("{:>2}", house_block[i][j][k]); 
        }
        }
    }


    /*
    const size_t num_cols{3};

    int packages2 [] [5] {
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {10,11,12},
                {100,110,120} // Can add as many triplets in packages2 as we want
    };

        fmt::println( std::endl;
    fmt::println( "Ommiting leftmost dimension for 2d array : " << std::endl;
    for (size_t i{0} ; i < std::size(packages2) ; ++i){
        for( size_t j{0} ; j < std::size(packages2[i]) ; ++j){
            fmt::println( "Item (" << i << "," << j << ") : " << packages2[i][j] << std::endl;
        }
    }
    */

    // For 3d and really any multi dimensional array , you have to specify
    // the number of elements in []'s , only the left most is not mandatory.
    // Below is the example for 3D reproduced.Omitting the 5 or the 3 or both
    // will cause a compile error.
    /*
    int house_block1 [] [5] [3] {

        {
            {1,2,3},{4,5,6},{7,8,9},{10,11,12},{13,14,15}
        },
        {
            {16,17,18},{19,20,21},{22,23,24},{25,26,27},{28,29,30}
        },
        {
            { 31,32,33},{34,35,36},{37,38,39},{40,41,42},{43,44,45}
        },
        {
            {46,47,48},{49,50,51},{52,53,54},{55,56,57},{58,59,60}
        }

    };

        for (size_t i {0} ; i < std::size(house_block1 ); ++i){

        for( size_t j{0}; j < std::size(house_block1[i]) ; ++j){

                        fmt::println( "[";
            for( size_t k{0}; k < std::size(house_block1[i][j]) ; ++k){

                fmt::println( house_block1[i][j][k] << " ";
            }
            fmt::println("] " ;//Separate elements for good visualization
        }
        fmt::println( std::endl;//Separate elements for good visualization
    }

    */


    // If you put less elements than the amount specified in the declaration, the compiler
    // will automaticaly fill out those left out with 0 or '\0' is the array is of char.
    //  Change the array to int house_block [] [5] [4], and because all inner arrays have 3,
    //  elements, the fourth will be autofilled with 0.
    //  Also remove some other elements, I chose the {4,5,6} array but you can add others
    //  when recording to make this a bit fun. The left out indexes will be auto filled with
    //  zeros
    /*
    int house_block2[][5][4]{
        // Try to make the last dimension 5 and show
        //that the compiler appends 2 zeros
        {
            {1, 2, 3}, {4}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15} //The one element array will be autofilled
            // with zeros to complete 4 elements
        },
        {
            {16, 17, 18}, {19, 20, 21}, {22, 23, 24}, {25, 26, 27}, {28, 29, 30}
        },
        {
            {31, 32, 33}, {34, 35, 36}, {37, 38, 39}, {40, 41, 42}, {43, 44, 45}
        },
        {
            {46, 47, 48}, {49, 50, 51}, {52, 53, 54}, {55, 56, 57} //,{58,59,60}  // The spots for {58,59,60
            // Will be autofilled with 0
        }

    };

    //Modify data
    house_block2[0][2][1] = 1021;

    fmt::println("Printing out 3d house_block array with defaulted elements : ");

    for (size_t i{0}; i < std::size(house_block2); ++i) {
        for (size_t j{0}; j < std::size(house_block2[i]); ++j) {
            fmt::println("[");
            for (size_t k{0}; k < std::size(house_block2[i][j]); ++k) {
                fmt::println("{} ", house_block2[i][j][k]);
            }
            fmt::println("] "); //Separate elements for good visualization
        }
        fmt::print("\n"); //Separate elements for good visualization
    }
    */
}

export void multi_dim_array_of_characters(){

    const size_t name_length{ 15 };

    char members[][name_length]{ { 'J', 'o', 'h', 'n' },
        {
        'S',
        'a',
        'm',
        'u',
        'e',
        'l',
        },
        { 'R', 'a', 's', 'h', 'i', 'd' },
        { 'R', 'o', 'd', 'r', 'i', 'g', 'e', 'z' } };

    // Declaring a 2D array

    // Printing out like this is unsafe : may go over and print
    // outside your valid memory block
    // until a terminating null character is encountered.
    /*fmt::println( "Unsafe printing of members : " );
    for (size_t i {0}; i < std::size(members) ; ++i){
    fmt::println( "{}", members[i] );
    }*/


    // Can loop around manually printing out each character
    /*fmt::println( "Printing out character by character manually : " );
    for (size_t i{0} ; i < std::size(members) ; ++i){
        for (size_t j{0} ; j < std::size(members[i]) ; ++j){
            fmt::println( "{}", members[i][j] );
        }
    }*/

    // Better : Using C-string litterals
    // Compared to initialization with charactes with in '', this
    //  is even easier to type. The entire string is a single entity
    // you can manage easily.
    /*char members1 [][name_length] {
        "John",
        "Samuel",
        "Rashid",
        "Rodriguez"
    };

    //Printing out members1
    fmt::println( "Printing out members1 (C-string literals) : " );
    for (size_t i {0}; i < std::size(members1) ; ++i){
        fmt::println( "{}", members1[i] );
    }*/


    // Storing string literals
    char predictions[][90]{ "a lot of kids running in the backyard!",
        "a lot of empty beer bootles on your work table.",
        "you Partying too much with kids wearing weird clothes.",
        "you running away from something really scary",
        "clouds gathering in the sky and an army standing ready for war",
        "dogs running around in a deserted empty city",
        "a lot of cars stuck in a terrible traffic jam",
        "you sitting in the dark typing lots of lines of code on your dirty computer",
        "you yelling at your boss. And oh no! You get fired!",
        "you laughing your lungs out. I've never seen this before.",
        "Uhm , I don't see anything!"

    };

    fmt::println("Prediction : {}", predictions[5]);
}


