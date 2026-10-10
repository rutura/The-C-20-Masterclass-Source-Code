# Answer key for the notes: a static library with MinGW GCC, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# 1. The library's source files become object files, as in 7.12.
Step g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
Step g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o

# 2. ar bundles the objects into an archive. r = insert, c = create quietly,
#    s = write a symbol index so the linker can find things fast.
Step ar rcs libstation.a stats.o report.o

# 3. Look inside the archive: t = list the members, tv = with sizes.
Step ar t libstation.a
Step ar tv libstation.a
nm -C libstation.a | Select-String to_celsius

# 4. The program itself, then link it against the archive.
#    -L. = also search this folder, -lstation = find libstation.a
Step g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
Step g++ main.o -L. -lstation -o weather.exe -lstdc++exp

Step .\weather.exe
