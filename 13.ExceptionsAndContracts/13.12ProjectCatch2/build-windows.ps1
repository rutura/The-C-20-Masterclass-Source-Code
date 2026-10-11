# Answer key for the notes: build and test with vcpkg manifest mode, on Windows.
# Run from a Developer PowerShell for VS, inside this folder.
#
# VCPKG_ROOT must point at a vcpkg. In the Developer PowerShell it already
# points at the copy that comes with Visual Studio. If you installed your own,
# point it there first:   $env:VCPKG_ROOT = 'C:\dev\vcpkg'

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    $rest = @($args | Select-Object -Skip 1)       # empty when the command has no arguments
    & $args[0] @rest
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

Write-Host "VCPKG_ROOT = $env:VCPKG_ROOT"

# The first configure reads vcpkg.json and builds catch2 (a few minutes the
# first time, quick afterwards thanks to vcpkg's binary cache).
Step cmake --preset default
Step cmake --build --preset default

# Two ways to run the tests: the executable itself, or CTest.
Step .\build\rooster.exe
Step ctest --preset default
