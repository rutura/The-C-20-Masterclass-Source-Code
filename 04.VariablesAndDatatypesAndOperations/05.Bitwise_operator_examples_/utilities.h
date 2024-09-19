#pragma once
#include <string_view>

constexpr unsigned char mask_bit_0{ 0b00000001 };// Bit0
constexpr unsigned char mask_bit_1{ 0b00000010 };// Bit1
constexpr unsigned char mask_bit_2{ 0b00000100 };// Bit2
constexpr unsigned char mask_bit_3{ 0b00001000 };// Bit3
constexpr unsigned char mask_bit_4{ 0b00010000 };// Bit4
constexpr unsigned char mask_bit_5{ 0b00100000 };// Bit5
constexpr unsigned char mask_bit_6{ 0b01000000 };// Bit6
constexpr unsigned char mask_bit_7{ 0b10000000 };// Bit7

void print_msg(std::string_view msg);
void use_options_v0(bool flag0, bool flag1, bool flag2, bool flag3, bool flag4, bool flag5, bool flag6, bool flag7);
void use_options_v1(unsigned char flags);
void pack_colors();