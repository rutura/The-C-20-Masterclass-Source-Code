# Chapter 26: Enums, Type Aliases & Bitwise Operators

## Why these three topics share a chapter

Enums, type aliases, and bitwise operators are all, in their own way, about
giving a value a better name or a smaller footprint - an `enum class` names
a closed set of options instead of a bare integer, a type alias gives a
long or unwieldy type a short readable name, and bitwise operators let
several small values share one integer's worth of storage. None of the
three is large enough to earn its own chapter, and the last lecture on
enums (flags with `enum class`) is also the natural doorway into bitwise
operators, so the two topics that used to be separate chapters are
concatenated here instead - enums and aliases first, then bitwise
operators building directly on the `enum class` this chapter just taught.

## Lecture by lecture

- **27.2 Enum Classes** - declaring a scoped `enum class`, giving it an
  explicit underlying type sized to what it actually needs to hold.
- **27.3 Using Enum** - `using enum` to bring a scoped enum's enumerators
  into scope unqualified, useful once a `switch` has to name every one of
  them.
- **27.4 Old Enums** - plain (unscoped) enums, shown *after* `enum class`
  rather than before, to make their looser rules - enumerators leaking into
  the surrounding scope, implicit conversion to their underlying type - read
  as the problem `enum class` was introduced to fix, not as the default way
  to write an enum.
- **27.5 Type Aliases** - `using` as the modern way to name a type,
  contrasted with the older `typedef` syntax it replaced.
- **27.6 Shift and Logical Operators** - `<<` and `>>` to shift bits left
  and right, and `& | ^ ~` to combine or flip them bit-by-bit.
- **27.7 Flags with enum class** - the realistic use case: naming a handful
  of on/off options with the `enum class` from earlier in this chapter,
  giving each one its own bit, and combining them with `|` - plus why
  `enum class` requires an explicit cast to do it, unlike a plain `enum`.
- **27.8 Packing Data into an Integer** - one compact example (packing a
  32-bit color from four separate channels) showing why you'd bother: many
  small values riding around as a single, easily copied integer.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
