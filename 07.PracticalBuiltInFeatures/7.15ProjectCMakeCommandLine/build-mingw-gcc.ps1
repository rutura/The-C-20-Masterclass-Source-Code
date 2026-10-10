# Answer key for the notes: driving CMake from the command line with MinGW GCC.
# Needs C:\mingw64\bin on PATH. Run in a normal PowerShell (not the VS
# Developer PowerShell, whose cl would be picked up first), inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# 1. Configure. Nothing tells CMake to use GCC except these two options.
#    Without them it would pick whatever it finds first.
Step cmake -S . -B build-mingw-gcc -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
Step cmake --build build-mingw-gcc --verbose

Step .\build-mingw-gcc\rooster.exe

# 3. Build only one target (just the library).
Step cmake --build build-mingw-gcc --target station

# 4. Same sources, different answer: ask for a DLL instead of a static library.
Step cmake -S . -B build-mingw-gcc-shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON
Step cmake --build build-mingw-gcc-shared
Get-ChildItem build-mingw-gcc-shared\*.dll, build-mingw-gcc-shared\*.a | Select-Object Name
Step .\build-mingw-gcc-shared\rooster.exe

# 5. Install the static build into a folder, to see what "install" means.
Step cmake --install build-mingw-gcc --prefix install-mingw-gcc
Get-ChildItem install-mingw-gcc -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
