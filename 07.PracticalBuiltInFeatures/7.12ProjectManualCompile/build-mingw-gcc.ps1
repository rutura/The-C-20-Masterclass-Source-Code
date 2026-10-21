# Answer key for the notes: MinGW GCC on Windows, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-mingw-gcc, so deleting that one
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

# -lstdc++exp: GCC 14's std::println needs this extra library.
# It goes AFTER the objects that need it.

New-Item -ItemType Directory -Force out-mingw-gcc | Out-Null

# 1. Single file, two steps
Step g++ -std=c++23 -Wall -Wextra -c single.cpp -o out-mingw-gcc/single.o
Step g++ out-mingw-gcc/single.o -o out-mingw-gcc/single_two_step.exe -lstdc++exp
Step ./out-mingw-gcc/single_two_step.exe

# 2. Read the object files and the binary
Step g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-gcc/stats.o
Step g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-gcc/report.o
Step objdump -f out-mingw-gcc/stats.o
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# U means "undefined here, the linker must find it".
nm out-mingw-gcc/stats.o | Select-String station
nm -C out-mingw-gcc/stats.o | Select-String station
nm out-mingw-gcc/report.o | Select-String to_celsius
Step c++filt _ZN7station10to_celsiusEd
Step objdump -f out-mingw-gcc/single_two_step.exe
objdump -p out-mingw-gcc/single_two_step.exe | Select-String 'DLL Name'

# 3. Single file, one step
Step g++ -std=c++23 -Wall -Wextra single.cpp -o out-mingw-gcc/single_one_step.exe -lstdc++exp
Step ./out-mingw-gcc/single_one_step.exe
Get-ChildItem out-mingw-gcc/single.o, out-mingw-gcc/single_two_step.exe, out-mingw-gcc/single_one_step.exe | Format-Table Name, Length -AutoSize

# 4. Multiple files: three objects, one link
Step g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-gcc/stats.o
Step g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-gcc/report.o
Step g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-gcc/main.o
Step g++ out-mingw-gcc/main.o out-mingw-gcc/stats.o out-mingw-gcc/report.o -o out-mingw-gcc/weather.exe -lstdc++exp
Step ./out-mingw-gcc/weather.exe

# Break it on purpose: leave stats.o out
StepMustFail g++ out-mingw-gcc/main.o out-mingw-gcc/report.o -o out-mingw-gcc/broken.exe -lstdc++exp
