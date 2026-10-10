# Answer key for the notes: the Memory Detective with MSVC.
# Run from a Developer PowerShell for VS, inside this folder.
# The sanitizer needs the "C++ AddressSanitizer" component of the Visual Studio
# installer (it is part of the "Desktop development with C++" workload).

$ErrorActionPreference = 'Stop'

function Step {
    Write-Host "> $args"
    & $args[0] $args[1..($args.Length - 1)]
    if ($LASTEXITCODE -ne 0) { throw "failed: $args" }
}

# Build 1: AddressSanitizer. /Zi gives the report file names and line numbers.
Step cl /nologo /std:c++latest /EHsc /MD /W4 /Zi /fsanitize=address main.cpp /Fe:detective.exe

# Run each buggy case. The sanitizer prints its report on stderr, stops the
# program and exits non-zero, which is not a script failure here. Going through
# cmd /c keeps PowerShell from turning the stderr text into an error. Only the
# top of each report is shown.
foreach ($case in 'heap-overflow', 'stack-overflow', 'use-after-free', 'double-free', 'stale-pointer') {
    Write-Host "`n=== $case"
    cmd /c ".\detective.exe $case 2>&1" | Select-Object -First 6
}

# These two get through the sanitizer unnoticed on MSVC:
#   leak             AddressSanitizer on Windows does not report leaks
#   signed-overflow  there is no undefined-behaviour sanitizer in MSVC
Write-Host "`n=== leak (ASan build: nothing reported)"
.\detective.exe leak
Write-Host "`n=== signed-overflow (silently wraps)"
.\detective.exe signed-overflow

# Every fixed case runs clean.
Write-Host "`n=== fixed versions"
foreach ($case in 'heap-overflow', 'stack-overflow', 'use-after-free', 'double-free', 'leak', 'stale-pointer', 'signed-overflow') {
    .\detective.exe $case fixed | Out-Null
    Write-Host ("{0,-16} exit code {1}" -f $case, $LASTEXITCODE)
}

# Build 2: the Debug runtime. /MDd and _DEBUG turn on the leak report that is
# printed when the program ends. It cannot be combined with /fsanitize=address
# in this project, so it is a separate build.
Step cl /nologo /std:c++latest /EHsc /MDd /W4 /Zi /D_DEBUG main.cpp /Fe:detective_debug.exe

Write-Host "`n=== leak (Debug CRT)"
.\detective_debug.exe leak
Write-Host "`n=== leak, fixed (Debug CRT: no report)"
.\detective_debug.exe leak fixed
