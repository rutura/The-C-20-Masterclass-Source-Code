# Answer key for the notes: a DLL with MSVC on Windows, no CMake.
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

# 1. Build the library. /LD makes a DLL. /DSTATION_BUILD_DLL turns STATION_API
#    into dllexport. Next to the DLL come station.lib (an IMPORT library, not
#    the code), station.exp (a by-product) and the object files.
Step cl @flags /DSTATION_BUILD_DLL /LD stats.cpp report.cpp /Fo:out-msvc\ /Fe:out-msvc\station.dll
Get-ChildItem out-msvc | Format-Table Name, Length -AutoSize

# 2. Look inside the DLL: the exported names, in MSVC's mangled form.
Step dumpbin /exports out-msvc\station.dll

# 3. Link the program against the import library, then ask what it needs.
Step cl @flags main.cpp out-msvc\station.lib /Fo:out-msvc\ /Fe:out-msvc\weather.exe
dumpbin /dependents out-msvc\weather.exe | Select-String 'station|MSVCP'

# 4. Run it. Windows looks for station.dll next to the .exe first.
Step .\out-msvc\weather.exe

# 5. Break it on purpose
# 5a. The missing DLL is not in this script, because Windows may show a dialog
#     box and wait for a click. By hand: rename out-msvc\station.dll to
#     station.dll.away and run .\out-msvc\weather.exe. It does not start.
# 5b. Leave the library out of the link
StepMustFail cl @flags main.cpp /Fo:out-msvc\ /Fe:out-msvc\broken.exe

# 6. Replace the library without relinking the program: build a second version
#    from stats.cpp + report_v2.cpp, copy it over the old DLL, run the SAME exe.
New-Item -ItemType Directory -Force out-msvc\v2 | Out-Null
Step cl @flags /DSTATION_BUILD_DLL /LD stats.cpp report_v2.cpp /Fo:out-msvc\v2\ /Fe:out-msvc\v2\station.dll
Copy-Item out-msvc\v2\station.dll out-msvc\station.dll -Force
Step .\out-msvc\weather.exe
