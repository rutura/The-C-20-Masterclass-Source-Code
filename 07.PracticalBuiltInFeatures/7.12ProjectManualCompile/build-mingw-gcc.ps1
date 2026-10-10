# Answer key for the notes: MinGW GCC on Windows, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# -lstdc++exp: GCC 14's std::println needs this extra library.
# It goes AFTER the objects that need it.

# Part 1: single file, two steps
Step g++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
Step g++ single.o -o single_two_step.exe -lstdc++exp

# Part 1 again: single file, one step
Step g++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step.exe -lstdc++exp

# Part 2: three source files, three objects, one link
Step g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
Step g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
Step g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
Step g++ main.o stats.o report.o -o weather.exe -lstdc++exp

Step .\weather.exe

# Part 3: look inside. COFF object, Itanium name mangling.
Step objdump -f stats.o
# A tiny program still drags in hundreds of std:: template symbols, so
# filter for our own namespace. U means "undefined here, the linker must find it".
nm stats.o | Select-String station
nm -C stats.o | Select-String station
nm report.o | Select-String to_celsius
