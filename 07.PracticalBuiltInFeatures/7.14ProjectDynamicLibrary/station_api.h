#pragma once

// One header decides what STATION_API means, depending on who is compiling.
//
//   Building the library itself  -> "I am providing this function"
//   Building a program using it  -> "this function lives in a library"
//
// On Windows a DLL exports nothing unless told to. On Linux every function is
// exported by default, which is why the Linux commands in the notes add
// -fvisibility=hidden: for your own code, it gives Linux the same "opt in"
// rule as Windows (the standard library's templates stay visible either way).
#if defined(_WIN32)
    #if defined(STATION_BUILD_DLL)
        #define STATION_API __declspec(dllexport)
    #else
        #define STATION_API __declspec(dllimport)
    #endif
#else
    #define STATION_API __attribute__((visibility("default")))
#endif
