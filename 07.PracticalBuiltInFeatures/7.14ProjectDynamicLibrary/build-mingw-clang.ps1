# Answer key for the notes: a DLL with MinGW Clang on Windows, no CMake.
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

# Two link options for std::println in the program (the DLL itself does not use println):
# -lstdc++exp: the libstdc++ that MinGW Clang uses needs this extra library. It
#   goes AFTER the objects that need it.
# -fuse-ld=lld: link with Clang's own linker. The default GNU ld refuses the
#   mix of Clang-built objects and GCC-built libstdc++exp.a, with "duplicate
#   section ... has different size" errors.

New-Item -ItemType Directory -Force out-mingw-clang | Out-Null

# 1. Build the library. -shared makes a DLL. STATION_BUILD_DLL turns STATION_API
#    into dllexport. In PowerShell the -Wl,... option must be quoted, because a
#    comma otherwise means "list of values". --out-implib also writes the import
#    library, the MinGW counterpart of MSVC's station.lib.
Step clang++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report.cpp -o out-mingw-clang\station.dll '-Wl,--out-implib,out-mingw-clang\libstation.dll.a'
Get-ChildItem out-mingw-clang | Format-Table Name, Length -AutoSize

# 2. Look inside the DLL: the exports table.
objdump -p out-mingw-clang\station.dll | Select-String 'station'

# 3. Link the program against the import library (-L<folder> -lstation finds
#    libstation.dll.a), then ask what it needs.
Step clang++ -std=c++23 -Wall -Wextra main.cpp -Lout-mingw-clang -lstation -o out-mingw-clang\weather.exe -fuse-ld=lld -lstdc++exp
objdump -p out-mingw-clang\weather.exe | Select-String 'DLL Name: (station|libstdc)'

# 4. Run it. Windows looks for station.dll next to the .exe first.
Step .\out-mingw-clang\weather.exe

# 5. Break it on purpose
# 5a. The missing DLL is not in this script, because Windows may show a dialog
#     box and wait for a click. By hand: rename out-mingw-clang\station.dll to
#     station.dll.away and run .\out-mingw-clang\weather.exe. It does not start.
# 5b. Leave the library out of the link
StepMustFail clang++ -std=c++23 -Wall -Wextra main.cpp -o out-mingw-clang\broken.exe -fuse-ld=lld -lstdc++exp
# 5c. Name the library but not the folder
StepMustFail clang++ -std=c++23 -Wall -Wextra main.cpp -lstation -o out-mingw-clang\broken.exe -fuse-ld=lld -lstdc++exp

# 6. Replace the library without relinking the program: build a second version
#    from stats.cpp + report_v2.cpp, copy it over the old DLL, run the SAME exe.
New-Item -ItemType Directory -Force out-mingw-clang\v2 | Out-Null
Step clang++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report_v2.cpp -o out-mingw-clang\v2\station.dll '-Wl,--out-implib,out-mingw-clang\v2\libstation.dll.a'
Copy-Item out-mingw-clang\v2\station.dll out-mingw-clang\station.dll -Force
Step .\out-mingw-clang\weather.exe
