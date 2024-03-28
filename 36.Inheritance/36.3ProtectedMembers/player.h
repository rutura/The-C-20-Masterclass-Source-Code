#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fmt/format.h>
#include <string_view>
#include "person.h"

class Player : public Person
{
    friend std::ostream& operator<<(std::ostream& out, const Player& player);
    friend struct fmt::formatter<Player>;
public:
    Player() = default;
    Player(std::string_view game_param, std::string_view first_name_param,
            std::string_view last_name_param);
private : 
    std::string m_game{"None"};
};

template<>
struct fmt::formatter<Player> {
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Player &obj, FormatContext &ctx) const {
        return format_to(ctx.out(), "Player [game: {}, names: {} {}]", obj.m_game, obj.get_first_name(),obj.get_last_name() );
    }
};

#endif // PLAYER_H