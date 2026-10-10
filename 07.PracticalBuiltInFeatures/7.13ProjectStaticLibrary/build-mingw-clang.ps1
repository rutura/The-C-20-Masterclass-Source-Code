# Answer key for the notes: a static library with MinGW Clang, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# Same shape as the GCC script. The archiver (ar) is the same tool, because
# the objects are the same COFF format.

# 1. The library's source files become object files, as in 7.12.
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o

# 2. Bundle the objects into an archive.
Step ar rcs libstation.a stats.o report.o

# 3. Look inside the archive.
Step ar t libstation.a
Step ar tv libstation.a
nm -C libstation.a | Select-String to_celsius

# 4. The program itself, then link it against the archive.
Step clang++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
Step clang++ main.o -L. -lstation -o weather.exe -lstdc++exp

Step .\weather.exe
