#ifndef STREAM_INSERTABLE_H
#define STREAM_INSERTABLE_H
#include <fmt/format.h>

class StreamInsertable{
    friend std::ostream& operator<< (std::ostream& out, const StreamInsertable& operand);
    friend struct fmt::formatter<StreamInsertable>;
public : 
    virtual void stream_insert(std::ostream& out)const =0;
    virtual void stream_insert(fmt::basic_memory_buffer<char>& out) const = 0;
};

template<>
struct fmt::formatter<StreamInsertable> {
    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const StreamInsertable& obj, FormatContext& ctx) {
        basic_memory_buffer<char> buf;
        obj.stream_insert(buf);
        return format_to(ctx.out(), "{}", buf);
    }
};

template<typename T>
std::string make_streamable(const T& obj) {
    fmt::memory_buffer buf;
    obj.stream_insert(buf);
    return fmt::to_string(buf);
}

void format_int_pointer_array(fmt::basic_memory_buffer<char>& out, int const* array, size_t size);

#endif //STREAM_INSERTABLE_H