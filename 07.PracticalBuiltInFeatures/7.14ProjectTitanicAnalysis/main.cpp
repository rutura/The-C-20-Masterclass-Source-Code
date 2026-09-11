#include <print>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

#include "rapidcsv.h"

// PROJECT: load the Titanic passenger list and pull real answers out of
// it - the payoff lecture for everything else in this chapter: vector,
// sorting, ranges/views, strings, and CSV loading, all on one dataset.

int main() {

    // ConverterParams{true} treats an unparseable cell (the dataset's "?"
    // for missing age) as NaN instead of throwing.
    rapidcsv::Document titanic{"titanic.csv",
        rapidcsv::LabelParams{}, rapidcsv::SeparatorParams{},
        rapidcsv::ConverterParams{true}};

    auto survived{titanic.GetColumn<int>("survived")};
    auto sex{titanic.GetColumn<std::string>("sex")};
    auto age{titanic.GetColumn<double>("age")};
    auto passenger_class{titanic.GetColumn<int>("pclass")};

    // --- a first look: first and last five rows -----------------------------
    std::println("First five passengers:");
    std::println("{:<10}{:<8}{:<6}{}", "survived", "sex", "age", "class");
    for (std::size_t i{0}; i < 5; ++i) {
        std::println("{:<10}{:<8}{:<6.1f}{}",
                      survived.at(i), sex.at(i), age.at(i), passenger_class.at(i));
    }

    const std::size_t row_count{titanic.GetRowCount()};
    std::println("\nLast five passengers:");
    std::println("{:<10}{:<8}{:<6}{}", "survived", "sex", "age", "class");
    for (std::size_t i{row_count - 5}; i < row_count; ++i) {
        std::println("{:<10}{:<8}{:<6.1f}{}",
                      survived.at(i), sex.at(i), age.at(i), passenger_class.at(i));
    }

    // --- descriptive statistics for age, with missing values dropped -------
    // A view lazily filters out the NaNs; only then do we copy the
    // survivors into a real vector to sort.
    auto known_ages{age | std::views::filter([](double a) { return !std::isnan(a); })};
    std::vector<double> clean_ages{known_ages.begin(), known_ages.end()};

    std::ranges::sort(clean_ages);
    const std::size_t known_count{clean_ages.size()};
    double median_age{};

    if (known_count % 2 == 0) {
        median_age = (clean_ages.at(known_count / 2 - 1) + clean_ages.at(known_count / 2)) / 2;
    }
    else {
        median_age = clean_ages.at(known_count / 2);
    }

    const double average_age{
        std::accumulate(clean_ages.begin(), clean_ages.end(), 0.0) / known_count};

    std::println("\nAge statistics (missing values excluded):");
    std::println("passengers with age data: {}", known_count);
    std::println("average age: {:.2f}", average_age);
    std::println("minimum age: {:.2f}", clean_ages.front());
    std::println("maximum age: {:.2f}", clean_ages.back());
    std::println("median age:  {:.2f}", median_age);

    // --- passenger counts by class ------------------------------------------
    auto count_in_class{
        [&passenger_class](int class_number) {
            return std::ranges::count_if(passenger_class,
                [class_number](int c) { return c == class_number; });
        }
    };

    std::println("\nPassenger counts by class:");
    std::println("1st: {}", count_in_class(1));
    std::println("2nd: {}", count_in_class(2));
    std::println("3rd: {}", count_in_class(3));

    // --- overall survival rate -----------------------------------------------
    const auto survivor_count{
        std::ranges::count_if(survived, [](int s) { return s != 0; })};

    std::println("\nSurvived: {}", survivor_count);
    std::println("Died:     {}", survived.size() - survivor_count);
    std::println("Survival rate: {:.2f}%",
                  100.0 * survivor_count / survived.size());

    // --- who survived: by sex and by class -----------------------------------
    int surviving_women{0};
    int surviving_men{0};
    int surviving_first_class{0};
    int surviving_second_class{0};
    int surviving_third_class{0};

    for (std::size_t i{0}; i < survived.size(); ++i) {
        if (!survived.at(i)) {
            continue;
        }

        sex.at(i) == "female" ? ++surviving_women : ++surviving_men;

        switch (passenger_class.at(i)) {
            case 1: ++surviving_first_class; break;
            case 2: ++surviving_second_class; break;
            default: ++surviving_third_class; break;
        }
    }

    std::println("\nOf the survivors:");
    std::println("female: {:.2f}%", 100.0 * surviving_women / survivor_count);
    std::println("male:   {:.2f}%", 100.0 * surviving_men / survivor_count);
    std::println("1st class: {:.2f}%", 100.0 * surviving_first_class / survivor_count);
    std::println("2nd class: {:.2f}%", 100.0 * surviving_second_class / survivor_count);
    std::println("3rd class: {:.2f}%", 100.0 * surviving_third_class / survivor_count);

    return 0;
}
