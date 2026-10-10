# Answer key for the notes: a DLL with MinGW Clang, no CMake.
# Needs C:\mingw64\bin on PATH. Run inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# Same shape as the GCC script.

# 1. Build the library as a DLL plus its import library. In PowerShell the
#    -Wl,... option must be quoted, because a comma otherwise means "list".
Step clang++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report.cpp -o station.dll '-Wl,--out-implib,libstation.dll.a'

# 2. The import library is small. The code is in the DLL.
Get-ChildItem station.dll, libstation.dll.a | Select-Object Name, Length

# 3. Look inside: the exports table of the DLL.
objdump -p station.dll | Select-String 'station'

# 4. Build the program against the import library.
Step clang++ -std=c++23 -Wall -Wextra main.cpp -L. -lstation -o weather.exe -lstdc++exp

# 5. Which DLLs will the program load at startup?
objdump -p weather.exe | Select-String 'DLL Name: (station|libstdc)'

# 6. Run it.
Step .\weather.exe

# 7. Try by hand, it is not in this script because Windows may show a
#    dialog box and wait for a click: rename station.dll to station.dll.away
#    and run .\weather.exe again. The program no longer starts.
