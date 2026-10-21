# Answer key for the notes: driving CMake from the command line with MinGW Clang.
# Needs C:\mingw64\bin on PATH. Run in a normal PowerShell (not the VS
# Developer PowerShell, whose cl would be picked up first), inside this folder.
# The steps are in the same order as the notes.
# Everything CMake and the compiler produce goes into out-mingw-clang, so
# deleting that one folder cleans up.

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

# For a command that succeeds but prints a warning on stderr (CMake does):
# without this, Windows PowerShell 5.1 would treat the warning as an error.
function StepWarn {
    Write-Host "> $args"
    $ErrorActionPreference = 'Continue'
    & $args[0] $args[1..($args.Length - 1)] 2>&1 | ForEach-Object { "$_" }
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# 1. Configure. Nothing tells CMake to use Clang except these two options.
#    Without them it would pick whatever it finds first.
Step cmake -S . -B out-mingw-clang/static -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
Get-ChildItem out-mingw-clang\static -Name
Select-String -Path out-mingw-clang\static\CMakeCache.txt -Pattern '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' | ForEach-Object { $_.Line }

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
Step cmake --build out-mingw-clang/static --verbose
Step .\out-mingw-clang\static\rooster.exe

# 3. Build again: nothing changed, then touch one source file.
Step cmake --build out-mingw-clang/static
(Get-Item stats.cpp).LastWriteTime = Get-Date
Step cmake --build out-mingw-clang/static

# 4. Build one target, and a different build type.
Step cmake -S . -B out-mingw-clang/release -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
Step cmake --build out-mingw-clang/release --target station --verbose
Get-ChildItem out-mingw-clang\release -Name
Step cmake --build out-mingw-clang/release
Step .\out-mingw-clang\release\rooster.exe

# 5. Same sources, different answer: ask for a DLL instead of a static library.
Step cmake -S . -B out-mingw-clang/shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON
Step cmake --build out-mingw-clang/shared --verbose
Get-ChildItem out-mingw-clang\shared\*.dll, out-mingw-clang\shared\*.a | Format-Table Name, Length -AutoSize
Step .\out-mingw-clang\shared\rooster.exe

# 6. Install both builds into folders, to see what "install" means.
Step cmake --install out-mingw-clang/static --prefix out-mingw-clang/install
Get-ChildItem out-mingw-clang\install -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
Step .\out-mingw-clang\install\bin\rooster.exe
Step cmake --install out-mingw-clang/shared --prefix out-mingw-clang/install-shared
Get-ChildItem out-mingw-clang\install-shared -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
Step .\out-mingw-clang\install-shared\bin\rooster.exe

# 7. Break it on purpose
# 7a. The source folder has no CMakeLists.txt
StepMustFail cmake -S out-mingw-clang -B out-mingw-clang/oops -G Ninja
# 7b. A target that does not exist
StepMustFail cmake --build out-mingw-clang/static --target stationn
# 7c. Build a folder that was never configured
StepMustFail cmake --build out-mingw-clang/nothere
# 7d. Change the compiler of a folder that is already configured. This is not
#     an error: CMake warns, throws its cache away and starts again. The C and C++
#     compilers can end up different, which is why one folder keeps one compiler.
Step cmake -S . -B out-mingw-clang/swap -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
StepWarn cmake -S . -B out-mingw-clang/swap -G Ninja -DCMAKE_CXX_COMPILER=g++
