#include <print>
#include <string_view>

enum class Month {
    Jan, Feb, Mar, Apr,
    May, Jun, Jul, Aug,
    Sep, Oct, Nov, Dec
};

std::string_view month_to_string(Month month) {
    // using enum brings every enumerator into scope unqualified, so each
    // case can read Jan instead of Month::Jan - handy once a switch has to
    // name every single enumerator, as this one does.
    using enum Month;
    switch (month) {
        case Jan: return "January";
        case Feb: return "February";
        case Mar: return "March";
        case Apr: return "April";
        case May: return "May";
        case Jun: return "June";
        case Jul: return "July";
        case Aug: return "August";
        case Sep: return "September";
        case Oct: return "October";
        case Nov: return "November";
        case Dec: return "December";
        default: return "None";
    }
}

int main() {

    Month month{Month::Apr};
    std::println("month : {}", month_to_string(month));

    return 0;
}