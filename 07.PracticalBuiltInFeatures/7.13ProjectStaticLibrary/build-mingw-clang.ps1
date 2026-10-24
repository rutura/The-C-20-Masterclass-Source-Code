# Answer key for the notes: a static library with MinGW Clang on Windows, no CMake.
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

# Two link options for std::println with MinGW Clang:
# -lstdc++exp: the libstdc++ that MinGW Clang uses needs this extra library. It
#   goes AFTER the objects and libraries that need it.
# -fuse-ld=lld: link with Clang's own linker. The default GNU ld refuses the
#   mix of Clang-built objects and GCC-built libstdc++exp.a, with "duplicate
#   section ... has different size" errors.

New-Item -ItemType Directory -Force out-mingw-clang | Out-Null

# 1. Build the library: two objects, then one archive.
#    ar: r = insert, c = create quietly, s = write a symbol index.
#    It is the same ar as with GCC, because the objects have the same format.
Step clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-clang/stats.o
Step clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-clang/report.o
Step ar rcs out-mingw-clang/libstation.a out-mingw-clang/stats.o out-mingw-clang/report.o
Step ar t out-mingw-clang/libstation.a
Step ar tv out-mingw-clang/libstation.a

# 2. Look inside the archive: the members are the original object files
nm -C out-mingw-clang/libstation.a | Select-String 'to_celsius|\.o:'
Get-ChildItem out-mingw-clang/stats.o, out-mingw-clang/report.o, out-mingw-clang/libstation.a | Format-Table Name, Length -AutoSize
# Take one member back out and compare it with the object we put in.
New-Item -ItemType Directory -Force out-mingw-clang/extracted | Out-Null
Step ar x --output out-mingw-clang/extracted out-mingw-clang/libstation.a stats.o
(Get-FileHash out-mingw-clang/stats.o).Hash -eq (Get-FileHash out-mingw-clang/extracted/stats.o).Hash

# 3. Link the program against the library.
#    -L<folder> = also search this folder, -lstation = find libstation.a
Step clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-clang/main.o
Step clang++ out-mingw-clang/main.o -Lout-mingw-clang -lstation -o out-mingw-clang/weather.exe -fuse-ld=lld -lstdc++exp
Step ./out-mingw-clang/weather.exe
Get-ChildItem out-mingw-clang/main.o, out-mingw-clang/weather.exe | Format-Table Name, Length -AutoSize

# 4. Break it on purpose
# 4a. Leave the library out
StepMustFail clang++ out-mingw-clang/main.o -o out-mingw-clang/broken.exe -fuse-ld=lld -lstdc++exp
# 4b. Library before the object that needs it. lld finds the library whatever the
#     order, so we ask for GNU ld by name: the order rule belongs to GNU ld.
#     No -lstdc++exp here (with ld it brings the duplicate-section errors back),
#     so the output also has two std::__open_terminal / __write_to_terminal lines.
StepMustFail clang++ -fuse-ld=ld -Lout-mingw-clang -lstation out-mingw-clang/main.o -o out-mingw-clang/broken.exe
# 4c. Forget -L
StepMustFail clang++ out-mingw-clang/main.o -lstation -o out-mingw-clang/broken.exe -fuse-ld=lld -lstdc++exp

# 5. The finished program does not need the library any more
Remove-Item out-mingw-clang/libstation.a
Step ./out-mingw-clang/weather.exe
