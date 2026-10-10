# Answer key for the notes: a DLL with MSVC, no CMake.
# Run from a Developer PowerShell for VS, inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

$flags = '/nologo', '/std:c++latest', '/EHsc', '/MD', '/W4'

# 1. Build the library. /LD makes a DLL. STATION_BUILD_DLL turns STATION_API
#    into dllexport. Three files come out: station.dll, station.lib, station.exp.
Step cl @flags /DSTATION_BUILD_DLL /LD stats.cpp report.cpp /Fe:station.dll

# 2. station.lib is NOT the library code. It is a small "import library" that
#    tells the linker which names live in station.dll.
Get-ChildItem station.dll, station.lib | Select-Object Name, Length

# 3. Look inside: the exported names, in MSVC's mangled form.
Step dumpbin /exports station.dll

# 4. Build the program. It links against the import library, not the DLL.
Step cl @flags main.cpp station.lib /Fe:weather.exe

# 5. Which DLLs will the program load at startup?
dumpbin /dependents weather.exe | Select-String 'station|MSVCP'

# 6. Run it. Windows looks for station.dll next to the .exe first.
Step .\weather.exe

# 7. Try by hand, it is not in this script because Windows may show a
#    dialog box and wait for a click: rename station.dll to station.dll.away
#    and run .\weather.exe again. The program no longer starts.
