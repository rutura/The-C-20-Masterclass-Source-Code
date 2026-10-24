# Answer key for the notes: a static library with MinGW GCC on Windows, no CMake.
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

# -lstdc++exp: MinGW GCC (16.2 too) keeps std::println support in this extra library.
# It goes AFTER the objects and libraries that need it.

New-Item -ItemType Directory -Force out-mingw-gcc | Out-Null

# 1. Build the library: two objects, then one archive.
#    ar: r = insert, c = create quietly, s = write a symbol index.
Step g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-gcc/stats.o
Step g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-gcc/report.o
Step ar rcs out-mingw-gcc/libstation.a out-mingw-gcc/stats.o out-mingw-gcc/report.o
Step ar t out-mingw-gcc/libstation.a
Step ar tv out-mingw-gcc/libstation.a

# 2. Look inside the archive: the members are the original object files
nm -C out-mingw-gcc/libstation.a | Select-String 'to_celsius|\.o:'
Get-ChildItem out-mingw-gcc/stats.o, out-mingw-gcc/report.o, out-mingw-gcc/libstation.a | Format-Table Name, Length -AutoSize
# Take one member back out and compare it with the object we put in.
New-Item -ItemType Directory -Force out-mingw-gcc/extracted | Out-Null
Step ar x --output out-mingw-gcc/extracted out-mingw-gcc/libstation.a stats.o
(Get-FileHash out-mingw-gcc/stats.o).Hash -eq (Get-FileHash out-mingw-gcc/extracted/stats.o).Hash

# 3. Link the program against the library.
#    -L<folder> = also search this folder, -lstation = find libstation.a
Step g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-gcc/main.o
Step g++ out-mingw-gcc/main.o -Lout-mingw-gcc -lstation -o out-mingw-gcc/weather.exe -lstdc++exp
Step ./out-mingw-gcc/weather.exe
Get-ChildItem out-mingw-gcc/main.o, out-mingw-gcc/weather.exe | Format-Table Name, Length -AutoSize

# 4. Break it on purpose
# 4a. Leave the library out
StepMustFail g++ out-mingw-gcc/main.o -o out-mingw-gcc/broken.exe -lstdc++exp
# 4b. Library before the object that needs it
StepMustFail g++ -Lout-mingw-gcc -lstation out-mingw-gcc/main.o -o out-mingw-gcc/broken.exe -lstdc++exp
# 4c. Forget -L
StepMustFail g++ out-mingw-gcc/main.o -lstation -o out-mingw-gcc/broken.exe -lstdc++exp

# 5. The finished program does not need the library any more
Remove-Item out-mingw-gcc/libstation.a
Step ./out-mingw-gcc/weather.exe
