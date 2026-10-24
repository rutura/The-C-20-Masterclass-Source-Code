# Answer key for the notes: MinGW Clang on Windows, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-mingw-clang, so deleting that one
# folder cleans up.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# For the "break it on purpose" step: the command must fail.
function StepMustFail {
    Write-Host "> $args"
    # Windows PowerShell 5.1 turns a native command's stderr into a terminating
    # error under 'Stop', so relax it here and print the messages as plain text.
    $ErrorActionPreference = 'Continue'
    & $args[0] $args[1..($args.Length - 1)] 2>&1 | ForEach-Object { "$_" }
    if ($LASTEXITCODE -eq 0) { throw "should have failed: $args" }
    Write-Host "(failed, as expected)"
}

# Two link options for std::println with MinGW Clang:
# -lstdc++exp: the libstdc++ that MinGW Clang uses needs this extra library. It
#   goes AFTER the objects that need it.
# -fuse-ld=lld: link with Clang's own linker. The default GNU ld refuses the
#   mix of Clang-built objects and GCC-built libstdc++exp.a, with "duplicate
#   section ... has different size" errors.

New-Item -ItemType Directory -Force out-mingw-clang | Out-Null

# 1. Single file, two steps
Step clang++ -std=c++23 -Wall -Wextra -c single.cpp -o out-mingw-clang/single.o
Step clang++ out-mingw-clang/single.o -o out-mingw-clang/single_two_step.exe -fuse-ld=lld -lstdc++exp
Step ./out-mingw-clang/single_two_step.exe

# 2. Read the object files and the binary
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-clang/stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-clang/report.o
Step objdump -f out-mingw-clang/stats.o
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# U means "undefined here, the linker must find it".
nm out-mingw-clang/stats.o | Select-String station
nm -C out-mingw-clang/stats.o | Select-String station
nm out-mingw-clang/report.o | Select-String to_celsius
Step c++filt _ZN7station10to_celsiusEd
Step objdump -f out-mingw-clang/single_two_step.exe
objdump -p out-mingw-clang/single_two_step.exe | Select-String 'DLL Name'

# 3. Single file, one step
Step clang++ -std=c++23 -Wall -Wextra single.cpp -o out-mingw-clang/single_one_step.exe -fuse-ld=lld -lstdc++exp
Step ./out-mingw-clang/single_one_step.exe
Get-ChildItem out-mingw-clang/single.o, out-mingw-clang/single_two_step.exe, out-mingw-clang/single_one_step.exe | Format-Table Name, Length -AutoSize

# 4. Multiple files: three objects, one link
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-clang/stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-clang/report.o
Step clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-clang/main.o
Step clang++ out-mingw-clang/main.o out-mingw-clang/stats.o out-mingw-clang/report.o -o out-mingw-clang/weather.exe -fuse-ld=lld -lstdc++exp
Step ./out-mingw-clang/weather.exe

# Break it on purpose: leave stats.o out
StepMustFail clang++ out-mingw-clang/main.o out-mingw-clang/report.o -o out-mingw-clang/broken.exe -fuse-ld=lld -lstdc++exp
