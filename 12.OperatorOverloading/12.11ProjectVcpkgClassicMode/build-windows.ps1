# Answer key for the notes: vcpkg in classic mode, on Windows.
# Run from a Developer PowerShell for VS, inside this folder.
#
# Visual Studio ships its own copy of vcpkg, but that one only works in manifest
# mode (12.12). Classic mode needs a vcpkg of your own, so step 1 makes one.
# Pass -VcpkgRoot to put it somewhere else, for example:  .\build-windows.ps1 -VcpkgRoot D:\dev\vcpkg

param(
    [string]$VcpkgRoot = 'C:\dev\vcpkg'
)

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# 1. Get vcpkg, once: clone the repository and build the vcpkg tool.
if (-not (Test-Path "$VcpkgRoot\vcpkg.exe")) {
    Step git clone https://github.com/microsoft/vcpkg $VcpkgRoot
    Step "$VcpkgRoot\bootstrap-vcpkg.bat" -disableMetrics
}

# VCPKG_ROOT tells vcpkg and CMake where this vcpkg lives.
$env:VCPKG_ROOT = $VcpkgRoot

# 2. Install a library. The default triplet on Windows is x64-windows: 64-bit,
#    dynamic (DLL) libraries.
Step "$VcpkgRoot\vcpkg.exe" install fmt

# 3. What is installed, and where?
Step "$VcpkgRoot\vcpkg.exe" list
Get-ChildItem "$VcpkgRoot\installed\x64-windows" -Directory | Select-Object Name
Get-ChildItem "$VcpkgRoot\installed\x64-windows\lib", "$VcpkgRoot\installed\x64-windows\bin" -Filter "fmt*" | Select-Object Name

# 4. Tell CMake about vcpkg with its toolchain file, build and run.
#    Ninja builds one configuration per folder, so ask for Release here.
Step cmake -S . -B build -G Ninja "-DCMAKE_TOOLCHAIN_FILE=$VcpkgRoot\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
Step cmake --build build
Step .\build\rooster.exe
