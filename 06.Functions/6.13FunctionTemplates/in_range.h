#pragma once

template <typename T>
bool in_range(T value, T low, T high) {
    return low <= value && value <= high;
}