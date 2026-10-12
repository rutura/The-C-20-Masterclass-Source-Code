# Answer key for the notes: MSVC on Windows, no CMake.
# Run from a Developer PowerShell for VS, inside this folder.
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

# /std:c++latest, never /std:c++23: cl ignores the latter and <print> breaks.
# /MD picks the shared C runtime, which is also what CMake uses by default.
$flags = '/nologo', '/std:c++latest', '/EHsc', '/MD', '/W4'

# 1. Single file, two steps (source -> object -> executable)
Step cl @flags /c single.cpp
Step link /nologo single.obj /OUT:single_two_step.exe
Step .\single_two_step.exe

# 2. Read the object files and the binary
Step cl @flags /c stats.cpp
Step cl @flags /c report.cpp
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# UNDEF means "not defined in this object, the linker must find it".
dumpbin /headers stats.obj | Select-String 'File Type|machine'
dumpbin /symbols stats.obj | Select-String 'External.*station'
dumpbin /symbols report.obj | Select-String 'UNDEF.*to_celsius'
Step undname '?to_celsius@station@@YANN@Z'
dumpbin /headers single_two_step.exe | Select-String 'File Type|machine|subsystem'
dumpbin /dependents single_two_step.exe

# 3. Single file, one step (cl drives the linker for us)
Step cl @flags single.cpp /Fe:single_one_step.exe
Step .\single_one_step.exe
Get-ChildItem single.obj, single_two_step.exe, single_one_step.exe | Format-Table Name, Length -AutoSize

# 4. Multiple files: three objects, one link
Step cl @flags /c stats.cpp
Step cl @flags /c report.cpp
Step cl @flags /c main.cpp
Step link /nologo main.obj stats.obj report.obj /OUT:weather.exe
Step .\weather.exe

# Break it on purpose: leave stats.obj out
StepMustFail link /nologo main.obj report.obj /OUT:broken.exe
