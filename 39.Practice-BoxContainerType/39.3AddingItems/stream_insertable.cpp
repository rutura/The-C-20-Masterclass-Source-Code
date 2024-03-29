#include "stream_insertable.h"


std::ostream& operator<< (std::ostream& out,const StreamInsertable& operand){
    operand.stream_insert(out);
    return out;
}

void format_int_pointer_array(fmt::basic_memory_buffer<char>& out, int const* array, size_t size)
{
    format_to_n(std::back_inserter(out), 1, "[");
    for (size_t i = 0; i < size; ++i) {
        format_to_n(std::back_inserter(out), 1, "{}", (array[i]));
        if (i < size - 1) {
            format_to_n(std::back_inserter(out), 1,", ");
        }
    }
    format_to_n(std::back_inserter(out), 1, "]");
}