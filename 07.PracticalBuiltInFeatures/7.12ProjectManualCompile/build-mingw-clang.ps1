# Answer key for the notes: MinGW Clang on Windows, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# Same shape as the GCC script. This clang targets x86_64-w64-windows-gnu, so
# it produces the same COFF objects and the same Itanium mangled names as GCC.
# -lstdc++exp is needed for std::println, same as with GCC.

# Part 1: single file, two steps
Step clang++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
Step clang++ single.o -o single_two_step.exe -lstdc++exp

# Part 1 again: single file, one step
Step clang++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step.exe -lstdc++exp

# Part 2: three source files, three objects, one link
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
Step clang++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
Step clang++ main.o stats.o report.o -o weather.exe -lstdc++exp

Step .\weather.exe

# Part 3: look inside
Step objdump -f stats.o
# A tiny program still drags in hundreds of std:: template symbols, so
# filter for our own namespace. U means "undefined here, the linker must find it".
nm stats.o | Select-String station
nm -C stats.o | Select-String station
nm report.o | Select-String to_celsius
