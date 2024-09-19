#pragma once

constexpr int inc_mult(int a, int b)
{
    int result = ((++a) * (++b));
    return result;
}
