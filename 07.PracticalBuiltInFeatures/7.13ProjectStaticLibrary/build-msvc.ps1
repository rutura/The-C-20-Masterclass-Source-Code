# Answer key for the notes: a static library with MSVC, no CMake.
# Run from a Developer PowerShell for VS, inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

$flags = '/nologo', '/std:c++latest', '/EHsc', '/MD', '/W4'

# 1. The library's source files become object files, as in 7.12.
Step cl @flags /c stats.cpp
Step cl @flags /c report.cpp

# 2. The librarian bundles the objects into one archive. Nothing is linked yet.
Step lib /nologo /OUT:station.lib stats.obj report.obj

# 3. Look inside the archive: the members are the original object files.
Step lib /nologo /LIST station.lib
dumpbin /symbols station.lib | Select-String 'to_celsius'

# 4. The program itself, then link it against the archive.
Step cl @flags /c main.cpp
Step link /nologo main.obj station.lib /OUT:weather.exe

Step .\weather.exe
