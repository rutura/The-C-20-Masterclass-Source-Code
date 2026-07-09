# Renders slides.pdf for every lecture folder that has a slides.md,
# using the masterclass-slides Docker image (see slides/README.md).
#
# The lecture folder and slides/ (which holds theme.css) are mounted as
# siblings under /work rather than mounting theme.css directly inside the
# lecture folder - Marp CLI only resolves --theme-set files that live
# under its working directory, and mounting a single file straight into
# an already-mounted host folder makes Docker Desktop on Windows silently
# materialize an empty placeholder file back on the host. Mounting slides/
# itself as a read-only sibling avoids both problems.

$imageExists = docker images -q masterclass-slides
if (-not $imageExists) {
    docker build -t masterclass-slides slides
    if (-not $?) { exit 1 }
}

$decks = Get-ChildItem -Path . -Filter "slides.md" -Recurse |
    Where-Object { $_.FullName -notmatch '\\slides\\' }

foreach ($deck in $decks) {
    $dir = $deck.DirectoryName
    Write-Host "=== $dir ==="

    docker run --rm `
        -v "${dir}:/work/lecture" `
        -v "${PWD}\slides:/work/slides:ro" `
        -w /work/lecture `
        masterclass-slides slides.md --theme-set /work/slides/theme.css --pdf --allow-local-files -o slides.pdf

    if (-not $?) { exit 1 }
}
