# Answer key for the notes: driving CMake from the command line with MSVC.
# Run from a Developer PowerShell for VS, inside this folder.
# The steps are in the same order as the notes.
# Everything CMake and the compiler produce goes into out-msvc, so deleting
# that one folder cleans up.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# For the "break it on purpose" steps: the command must fail.
function StepMustFail {
    Write-Host "> $args"
    # Windows PowerShell 5.1 turns a native command's stderr into a terminating
    # error under 'Stop', so relax it here and print the messages as plain text.
    $ErrorActionPreference = 'Continue'
    & $args[0] $args[1..($args.Length - 1)] 2>&1 | ForEach-Object { "$_" }
    if ($LASTEXITCODE -eq 0) { throw "should have failed: $args" }
    Write-Host "(failed, as expected)"
}

# 1. Configure: read CMakeLists.txt and generate build files into out-msvc/static.
#    -S = where the source is, -B = where the build goes, -G = which generator.
#    The Developer PowerShell puts cl on PATH, so CMake finds it by itself.
Step cmake -S . -B out-msvc/static -G Ninja
Get-ChildItem out-msvc\static -Name
Select-String -Path out-msvc\static\CMakeCache.txt -Pattern '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:)' | ForEach-Object { $_.Line }

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
Step cmake --build out-msvc/static --verbose
Step .\out-msvc\static\rooster.exe

# 3. Build again: nothing changed, then touch one source file.
Step cmake --build out-msvc/static
(Get-Item stats.cpp).LastWriteTime = Get-Date
Step cmake --build out-msvc/static

# 4. Build one target, and a different build type.
Step cmake -S . -B out-msvc/release -G Ninja -DCMAKE_BUILD_TYPE=Release
Step cmake --build out-msvc/release --target station --verbose
Get-ChildItem out-msvc\release -Name
Step cmake --build out-msvc/release
Step .\out-msvc\release\rooster.exe

# 5. Same sources, different answer: ask for a DLL instead of a static library.
Step cmake -S . -B out-msvc/shared -G Ninja -DBUILD_SHARED_LIBS=ON
Step cmake --build out-msvc/shared --verbose
Get-ChildItem out-msvc\shared\*.dll, out-msvc\shared\*.lib | Format-Table Name, Length -AutoSize
Step .\out-msvc\shared\rooster.exe

# 6. Install both builds into folders, to see what "install" means.
Step cmake --install out-msvc/static --prefix out-msvc/install
Get-ChildItem out-msvc\install -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
Step .\out-msvc\install\bin\rooster.exe
Step cmake --install out-msvc/shared --prefix out-msvc/install-shared
Get-ChildItem out-msvc\install-shared -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
Step .\out-msvc\install-shared\bin\rooster.exe

# 7. Break it on purpose
# 7a. The source folder has no CMakeLists.txt
StepMustFail cmake -S out-msvc -B out-msvc/oops -G Ninja
# 7b. A target that does not exist
StepMustFail cmake --build out-msvc/static --target stationn
# 7c. Build a folder that was never configured
StepMustFail cmake --build out-msvc/nothere
# 7d. Another generator in a folder that already has one
StepMustFail cmake -S . -B out-msvc/static -G "NMake Makefiles"
