# Answer key for the notes: MinGW Clang on Windows, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.
# The steps are in the same order as the notes.

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

# -lstdc++exp: the libstdc++ that MinGW Clang uses needs this extra library
# for std::println. It goes AFTER the objects that need it.

# 1. Single file, two steps
Step clang++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
Step clang++ single.o -o single_two_step.exe -lstdc++exp
Step .\single_two_step.exe

# 2. Read the object files and the binary
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
Step objdump -f stats.o
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# U means "undefined here, the linker must find it".
nm stats.o | Select-String station
nm -C stats.o | Select-String station
nm report.o | Select-String to_celsius
Step c++filt _ZN7station10to_celsiusEd
Step objdump -f single_two_step.exe
objdump -p single_two_step.exe | Select-String 'DLL Name'

# 3. Single file, one step
Step clang++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step.exe -lstdc++exp
Step .\single_one_step.exe
Get-ChildItem single.o, single_two_step.exe, single_one_step.exe | Format-Table Name, Length -AutoSize

# 4. Multiple files: three objects, one link
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
Step clang++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
Step clang++ main.o stats.o report.o -o weather.exe -lstdc++exp
Step .\weather.exe

# Break it on purpose: leave stats.o out
StepMustFail clang++ main.o report.o -o broken.exe -lstdc++exp
