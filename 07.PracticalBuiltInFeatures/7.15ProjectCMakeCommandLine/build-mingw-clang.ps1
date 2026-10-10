# Answer key for the notes: driving CMake from the command line with MinGW Clang.
# Needs C:\mingw64\bin on PATH. Run in a normal PowerShell (not the VS
# Developer PowerShell, whose cl would be picked up first), inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# 1. Configure. Only the compiler options differ from the GCC script.
Step cmake -S . -B build-mingw-clang -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
Step cmake --build build-mingw-clang --verbose

Step .\build-mingw-clang\rooster.exe

# 3. Build only one target (just the library).
Step cmake --build build-mingw-clang --target station

# 4. Same sources, different answer: ask for a DLL instead of a static library.
Step cmake -S . -B build-mingw-clang-shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON
Step cmake --build build-mingw-clang-shared
Get-ChildItem build-mingw-clang-shared\*.dll, build-mingw-clang-shared\*.a | Select-Object Name
Step .\build-mingw-clang-shared\rooster.exe

# 5. Install the static build into a folder, to see what "install" means.
Step cmake --install build-mingw-clang --prefix install-mingw-clang
Get-ChildItem install-mingw-clang -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
