# Answer key for the notes: driving CMake from the command line with MSVC.
# Run from a Developer PowerShell for VS, inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# 1. Configure: read CMakeLists.txt and generate build files into build-msvc.
#    -S = where the source is, -B = where the build goes, -G = which generator.
#    The Developer PowerShell puts cl on PATH, so CMake finds it by itself.
Step cmake -S . -B build-msvc -G Ninja

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
Step cmake --build build-msvc --verbose

Step .\build-msvc\rooster.exe

# 3. Build only one target (just the library).
Step cmake --build build-msvc --target station

# 4. Same sources, different answer: ask for a DLL instead of a static library.
Step cmake -S . -B build-msvc-shared -G Ninja -DBUILD_SHARED_LIBS=ON
Step cmake --build build-msvc-shared
Get-ChildItem build-msvc-shared\*.dll, build-msvc-shared\*.lib | Select-Object Name
Step .\build-msvc-shared\rooster.exe

# 5. Install the static build into a folder, to see what "install" means.
Step cmake --install build-msvc --prefix install-msvc
Get-ChildItem install-msvc -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
