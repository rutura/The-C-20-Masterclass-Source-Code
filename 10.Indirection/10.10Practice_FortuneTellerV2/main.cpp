#include <iostream>
#include <print>
#include <random>

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());

    /*
    char prediction0[]{"a lot of kinds running in the backyard!"};
    char prediction1[]{"a lot of empty beer bootles on your work table."};
    char prediction2[]{"you Partying too much with kids wearing weird clothes."};
    char prediction3[]{"you running away from something really scary"};
    char prediction4[]{"clouds gathering in the sky and an army standing ready for war"};
    char prediction5[]{"dogs running around in a deserted empty city"};
    char prediction6[]{"a lot of cars stuck in a terrible traffic jam"};
    char prediction7[]{"you sitting in the dark typing lots of lines of code on your dirty computer"};
    char prediction8[]{"you yelling at your boss. And oh no! You get fired!"};
    char prediction9[]{"you laughing your lungs out. I've never seen this before."};
    */

    char predictions[][90]{
        "a lot of kinds running in the backyard!",
        "a lot of empty beer bootles on your work table.",
        "you Partying too much with kids wearing weird clothes.",
        "you running away from something really scary",
        "clouds gathering in the sky and an army standing ready for war",
        "dogs running around in a deserted empty city",
        "a lot of cars stuck in a terrible traffic jam",
        "you sitting in the dark typing lots of lines of code on your dirty computer",
        "you yelling at your boss. And oh no! You get fired!",
        "you laughing your lungs out. I've never seen this before.",
        ", huum, I don't see anything",
        "you drinking wine"};

    // The distribution's upper bound now tracks the array's own size, so
    // adding or removing a prediction doesn't require updating a magic
    // number anywhere else.
    std::uniform_int_distribution<size_t> dist(0, std::size(predictions) - 1);

    bool end{false};

    const int max_length{15};
    char name[max_length]{};

    std::println("What's your name dear :");
    std::cin.getline(name, max_length); // get input with spaces

    while (!end) {
        std::print("Oh dear {}, I see ", name);

        size_t rand_num = dist(gen);
        std::println("{}", predictions[rand_num]);

        /*
        switch (rand_num) { // [0~10]
            case 0:
                std::println("{}", prediction0);
                break;
            case 1:
                std::println("{}", prediction1);
                break;
            case 2:
                std::println("{}", prediction2);
                break;
            case 3:
                std::println("{}", prediction3);
                break;
            case 4:
                std::println("{}", prediction4);
                break;
            case 5:
                std::println("{}", prediction5);
                break;
            case 6:
                std::println("{}", prediction6);
                break;
            case 7:
                std::println("{}", prediction7);
                break;
            case 8:
                std::println("{}", prediction8);
                break;
            case 9:
                std::println("{}", prediction9);
                break;
            default:
                std::println(", huum, I don't see anything");
        }
        */

        std::print("Do you want me to try again ? (Y | N) : ");

        char go_on;
        std::cin >> go_on;

        end = ((go_on == 'Y') || (go_on == 'y')) ? false : true;
    }

    std::println("That's all I have for you today dear. Best wishes");

    return 0;
}
