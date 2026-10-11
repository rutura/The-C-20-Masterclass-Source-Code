import std;
import summary;

int main() {
    std::vector<double> temperatures{18.5, 24.0, 21.5, 12.0};
    std::println("--- Exercise 6: import std ---");
    std::println("{}", summary_of(temperatures));
    return 0;
}
