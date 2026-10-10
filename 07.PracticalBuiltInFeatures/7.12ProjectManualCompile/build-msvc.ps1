# Answer key for the notes: MSVC on Windows, no CMake.
# Run from a Developer PowerShell for VS, inside this folder.

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# /std:c++latest, never /std:c++23: cl ignores the latter and <print> breaks.
# /MD picks the shared C runtime, which is also what CMake uses by default.
$flags = '/nologo', '/std:c++latest', '/EHsc', '/MD', '/W4'

# Part 1: single file, two steps (source -> object -> executable)
Step cl @flags /c single.cpp
Step link /nologo single.obj /OUT:single_two_step.exe

# Part 1 again: single file, one step (cl drives the linker for us)
Step cl @flags single.cpp /Fe:single_one_step.exe

# Part 2: three source files, three objects, one link
Step cl @flags /c stats.cpp
Step cl @flags /c report.cpp
Step cl @flags /c main.cpp
Step link /nologo main.obj stats.obj report.obj /OUT:weather.exe

Step .\weather.exe

# Part 3: look inside. COFF object, MSVC name mangling.
# The headers dump is long. File type and machine are what we want.
dumpbin /headers stats.obj | Select-String 'File Type|machine'
# Plenty of std:: symbols in there, so look only at our own namespace.
# UNDEF means "not defined in this object, the linker must find it".
dumpbin /symbols stats.obj | Select-String station
dumpbin /symbols report.obj | Select-String to_celsius
undname '?to_celsius@station@@YANN@Z'
