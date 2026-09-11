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
    auto passengerClass{titanic.GetColumn<int>("pclass")};

    // --- a first look: first and last five rows -----------------------------
    std::println("First five passengers:");
    std::println("{:<10}{:<8}{:<6}{}", "survived", "sex", "age", "class");
    for (std::size_t i{0}; i < 5; ++i) {
        std::println("{:<10}{:<8}{:<6.1f}{}",
                      survived.at(i), sex.at(i), age.at(i), passengerClass.at(i));
    }

    const std::size_t rowCount{titanic.GetRowCount()};
    std::println("\nLast five passengers:");
    std::println("{:<10}{:<8}{:<6}{}", "survived", "sex", "age", "class");
    for (std::size_t i{rowCount - 5}; i < rowCount; ++i) {
        std::println("{:<10}{:<8}{:<6.1f}{}",
                      survived.at(i), sex.at(i), age.at(i), passengerClass.at(i));
    }

    // --- descriptive statistics for age, with missing values dropped -------
    // A view lazily filters out the NaNs; only then do we copy the
    // survivors into a real vector to sort.
    auto knownAges{age | std::views::filter([](double a) { return !std::isnan(a); })};
    std::vector<double> cleanAges{knownAges.begin(), knownAges.end()};

    std::ranges::sort(cleanAges);
    const std::size_t knownCount{cleanAges.size()};
    double medianAge{};

    if (knownCount % 2 == 0) {
        medianAge = (cleanAges.at(knownCount / 2 - 1) + cleanAges.at(knownCount / 2)) / 2;
    }
    else {
        medianAge = cleanAges.at(knownCount / 2);
    }

    const double averageAge{
        std::accumulate(cleanAges.begin(), cleanAges.end(), 0.0) / knownCount};

    std::println("\nAge statistics (missing values excluded):");
    std::println("passengers with age data: {}", knownCount);
    std::println("average age: {:.2f}", averageAge);
    std::println("minimum age: {:.2f}", cleanAges.front());
    std::println("maximum age: {:.2f}", cleanAges.back());
    std::println("median age:  {:.2f}", medianAge);

    // --- passenger counts by class ------------------------------------------
    auto countInClass{
        [&passengerClass](int classNumber) {
            return std::ranges::count_if(passengerClass,
                [classNumber](int c) { return c == classNumber; });
        }
    };

    std::println("\nPassenger counts by class:");
    std::println("1st: {}", countInClass(1));
    std::println("2nd: {}", countInClass(2));
    std::println("3rd: {}", countInClass(3));

    // --- overall survival rate -----------------------------------------------
    const auto survivorCount{
        std::ranges::count_if(survived, [](int s) { return s != 0; })};

    std::println("\nSurvived: {}", survivorCount);
    std::println("Died:     {}", survived.size() - survivorCount);
    std::println("Survival rate: {:.2f}%",
                  100.0 * survivorCount / survived.size());

    // --- who survived: by sex and by class -----------------------------------
    int survivingWomen{0};
    int survivingMen{0};
    int survivingFirstClass{0};
    int survivingSecondClass{0};
    int survivingThirdClass{0};

    for (std::size_t i{0}; i < survived.size(); ++i) {
        if (!survived.at(i)) {
            continue;
        }

        sex.at(i) == "female" ? ++survivingWomen : ++survivingMen;

        switch (passengerClass.at(i)) {
            case 1: ++survivingFirstClass; break;
            case 2: ++survivingSecondClass; break;
            default: ++survivingThirdClass; break;
        }
    }

    std::println("\nOf the survivors:");
    std::println("female: {:.2f}%", 100.0 * survivingWomen / survivorCount);
    std::println("male:   {:.2f}%", 100.0 * survivingMen / survivorCount);
    std::println("1st class: {:.2f}%", 100.0 * survivingFirstClass / survivorCount);
    std::println("2nd class: {:.2f}%", 100.0 * survivingSecondClass / survivorCount);
    std::println("3rd class: {:.2f}%", 100.0 * survivingThirdClass / survivorCount);

    return 0;
}
