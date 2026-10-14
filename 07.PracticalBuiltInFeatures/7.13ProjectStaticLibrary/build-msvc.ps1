# Answer key for the notes: a static library with MSVC on Windows, no CMake.
# Run from a Developer PowerShell for VS, inside this folder.
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-msvc, so deleting that one folder
# cleans up.

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

# /std:c++latest, never /std:c++23: cl ignores the latter and <print> breaks.
# /MD picks the shared C runtime, which is also what CMake uses by default.
$flags = '/nologo', '/std:c++latest', '/EHsc', '/MD', '/W4'

New-Item -ItemType Directory -Force out-msvc | Out-Null

# 1. Build the library: two objects, then one archive
Step cl @flags /c stats.cpp /Fo:out-msvc\
Step cl @flags /c report.cpp /Fo:out-msvc\
Step lib /nologo /OUT:out-msvc\station.lib out-msvc\stats.obj out-msvc\report.obj
Step lib /nologo /LIST out-msvc\station.lib

# 2. Look inside the archive: the members are the original object files
dumpbin /symbols out-msvc\station.lib | Select-String 'to_celsius'
Get-ChildItem out-msvc\stats.obj, out-msvc\report.obj, out-msvc\station.lib | Format-Table Name, Length -AutoSize
# Take one member back out and compare it with the object we put in.
New-Item -ItemType Directory -Force out-msvc\extracted | Out-Null
Step lib /nologo /EXTRACT:out-msvc\stats.obj /OUT:out-msvc\extracted\stats.obj out-msvc\station.lib
(Get-FileHash out-msvc\stats.obj).Hash -eq (Get-FileHash out-msvc\extracted\stats.obj).Hash

# 3. Link the program against the library
Step cl @flags /c main.cpp /Fo:out-msvc\
Step link /nologo out-msvc\main.obj out-msvc\station.lib /OUT:out-msvc\weather.exe
Step .\out-msvc\weather.exe
Get-ChildItem out-msvc\main.obj, out-msvc\weather.exe | Format-Table Name, Length -AutoSize

# 4. Break it on purpose
# 4a. Leave the library out
StepMustFail link /nologo out-msvc\main.obj /OUT:out-msvc\broken.exe
# 4b. The order does not matter to MSVC's link: library first still works
Step link /nologo out-msvc\station.lib out-msvc\main.obj /OUT:out-msvc\order.exe
Step .\out-msvc\order.exe
# 4c. A library built with another C runtime option (/MT instead of /MD)
Step cl /nologo /std:c++latest /EHsc /MT /W4 /c stats.cpp /Fo:out-msvc\stats_mt.obj
Step lib /nologo /OUT:out-msvc\station_mt.lib out-msvc\stats_mt.obj out-msvc\report.obj
StepMustFail link /nologo out-msvc\main.obj out-msvc\station_mt.lib /OUT:out-msvc\mt.exe

# 5. The finished program does not need the library any more
Remove-Item out-msvc\station.lib
Step .\out-msvc\weather.exe
