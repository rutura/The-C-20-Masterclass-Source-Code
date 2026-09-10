#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <vector>

// std::optional<T> holds either a T or nothing. It is the honest return
// type for "this might not produce a value" - a lookup that can miss, a
// parse that can fail - instead of sentinel values like -1 or "" or a
// bare bool out-parameter.

struct Contact {
    std::string name{};
    std::string phone{};
};

// Return the phone number for a name, or std::nullopt if not found.
std::optional<std::string> find_phone(const std::vector<Contact>& book,
                                      std::string_view name) {
    for (const Contact& c : book) {
        if (c.name == name) {
            return c.phone;      // wraps the string in an optional
        }
    }
    return std::nullopt;         // the "no value" state
}

// Parse a percentage 0..100, or nothing if out of range.
std::optional<int> parse_percent(int raw) {
    if (raw < 0 || raw > 100) {
        return std::nullopt;
    }
    return raw;
}

int main() {
    std::vector<Contact> book{
        {"Ada", "555-0101"},
        {"Grace", "555-0170"},
    };

    // has_value() / the bool conversion test whether there is a value.
    auto ada{find_phone(book, "Ada")};
    if (ada.has_value()) {
        std::println("Ada: {}", *ada);            // * gets the value
    }

    auto linus{find_phone(book, "Linus")};
    std::println("Linus found? {}", linus.has_value());

    // value_or(fallback) - the value if present, otherwise the fallback.
    // The clean way to collapse "maybe" down to a definite result.
    std::println("Grace: {}", find_phone(book, "Grace").value_or("unknown"));
    std::println("Bjarne: {}", find_phone(book, "Bjarne").value_or("unknown"));

    // -> reaches members of the contained value.
    std::optional<Contact> maybe_contact{Contact{"Edsger", "555-0199"}};
    std::println("contact name via ->: {}", maybe_contact->name);

    // A chain of validations, each returning optional.
    for (int candidate : {42, -5, 100, 150}) {
        if (auto pct{parse_percent(candidate)}) {
            std::println("{:>4} is a valid percent", *pct);
        } else {
            std::println("{:>4} is out of range", candidate);
        }
    }

    // .value() also gets the value but THROWS std::bad_optional_access if
    // empty - use it only when you have already checked, or want the throw.
    std::optional<int> empty{};
    try {
        std::println("{}", empty.value());
    } catch (const std::bad_optional_access& ex) {
        std::println("empty.value() threw: {}", ex.what());
    }

    return 0;
}
