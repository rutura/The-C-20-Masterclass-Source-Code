# Answer key for the notes: vcpkg in manifest mode, on Windows.
# Run from a Developer PowerShell for VS, inside this folder.
#
# VCPKG_ROOT must point at a vcpkg. In the Developer PowerShell it already
# points at the copy that comes with Visual Studio. If you installed your own,
# point it there first:   $env:VCPKG_ROOT = 'C:\dev\vcpkg'

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

Write-Host "VCPKG_ROOT = $env:VCPKG_ROOT"

# vcpkg.json lists what this project needs. There is nothing to install by
# hand: the first configure reads the manifest, builds ftxui and puts it in
# build\vcpkg_installed. (The first run takes a few minutes. Later runs reuse
# vcpkg's binary cache and are quick.)
Step cmake --preset default

# CMakePresets.json already holds the generator, the toolchain file and the
# build type, so these commands carry no options.
Step cmake --build --preset default
Step .\build\rooster.exe

# Where did the libraries go? Inside the project's own build folder.
Get-ChildItem build\vcpkg_installed -Directory | Select-Object Name
Get-ChildItem build\vcpkg_installed\x64-windows\lib | Select-Object Name
