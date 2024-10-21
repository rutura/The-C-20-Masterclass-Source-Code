module;

#include <fmt/format.h>
#include <iostream>

export module stream_insertable;


export class StreamInsertable {
    friend std::ostream& operator<<(std::ostream& out, const StreamInsertable& operand);

public:
    virtual void stream_insert(std::ostream& out) const = 0;
};

// Implementation
export std::ostream& operator<<(std::ostream& out, const StreamInsertable& operand) {
    operand.stream_insert(out);
    return out;
}