# Chapter 15: Bitwise Operators

## Why this chapter is short, and comes after Enums

Bitwise operators work directly on the individual bits inside an integer -
shifting them, combining them, flipping them. It's real, occasionally
essential C++, but most application code goes a long time without needing to
hand-roll a bitmask: modern C++ reaches for an `enum class` (chapter 14) to
name a handful of options, or a library type, long before it reaches for raw
bit-twiddling. This chapter keeps the mechanics brief and spends its second
half on the one place bitwise operators still show up in realistic code -
combining flags - rather than working through every masking technique in
isolation.

## Lecture by lecture

- **15.2 Shift and Logical Operators** - `<<` and `>>` to shift bits left and
  right, and `& | ^ ~` to combine or flip them bit-by-bit, shown once,
  directly.
- **15.3 Flags with enum class** - the realistic use case: naming a handful
  of on/off options with an `enum class` (chapter 14), giving each one its
  own bit, and combining them with `|` - plus why `enum class` requires an
  explicit cast to do it, unlike a plain `enum`.
- **15.4 Packing Data into an Integer** - one compact example (packing a
  32-bit color from four separate channels) showing why you'd bother: many
  small values riding around as a single, easily copied integer.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
