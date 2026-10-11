# Answer key for the notes: build times of the three versions, on Windows.
# Run from a Developer PowerShell for VS, inside this folder:   .\compare-builds.ps1
# Every number is the MEDIAN of 3 runs, in milliseconds, of an unoptimized build
# (CMake's default with Ninja and MSVC is Debug). The clean build of the third
# version includes building the standard library module, once.

$ErrorActionPreference = 'Stop'
$src = $PSScriptRoot
$build = Join-Path $src 'build-compare'

cmake -S $src -B $build -G Ninja | Out-Null
cmake --build $build --target stb | Out-Null          # the shared library is not part of the comparison

function Ms($target) {
    (Measure-Command { cmd /c "cmake --build $build --target $target > nul 2>&1" }).TotalMilliseconds
}
function Median($values) { ($values | Sort-Object)[1] }

function CleanBuild($target) {
    Median (1..3 | ForEach-Object { cmd /c "ninja -C $build -t clean $target > nul 2>&1"; Ms $target })
}
function TouchBuild($target, $file) {
    cmd /c "cmake --build $build --target $target > nul 2>&1"
    Median (1..3 | ForEach-Object { (Get-Item (Join-Path $src $file)).LastWriteTime = Get-Date; Ms $target })
}

$rows = @(
    @('clean build',
        (CleanBuild 'rooster_headers'), (CleanBuild 'rooster'), (CleanBuild 'rooster_std')),
    @('touch color (the lowest file)',
        (TouchBuild 'rooster_headers' 'headers\color.h'), (TouchBuild 'rooster' 'modules\color.cppm'), (TouchBuild 'rooster_std' 'modules_std\color.cppm')),
    @('touch shapes (the top interface)',
        (TouchBuild 'rooster_headers' 'headers\shapes.h'), (TouchBuild 'rooster' 'modules\shapes.cppm'), (TouchBuild 'rooster_std' 'modules_std\shapes.cppm')),
    @('touch canvas.cpp (an implementation)',
        (TouchBuild 'rooster_headers' 'headers\canvas.cpp'), (TouchBuild 'rooster' 'modules\canvas.cpp'), (TouchBuild 'rooster_std' 'modules_std\canvas.cpp')),
    @('touch main.cpp',
        (TouchBuild 'rooster_headers' 'headers\main.cpp'), (TouchBuild 'rooster' 'modules\main.cpp'), (TouchBuild 'rooster_std' 'modules_std\main.cpp'))
)

'{0,-38} {1,11} {2,11} {3,11}' -f '', 'headers', 'modules', 'import std'
foreach ($r in $rows) {
    '{0,-38} {1,8} ms {2,8} ms {3,8} ms' -f $r[0], [math]::Round($r[1]), [math]::Round($r[2]), [math]::Round($r[3])
}
