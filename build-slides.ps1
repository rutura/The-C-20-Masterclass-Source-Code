# Renders slides.pdf for every lecture folder that has a slides.md,
# using the masterclass-slides Docker image (see slides/README.md).

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
        -v "${dir}:/home/marp/app" `
        -v "${PWD}\slides\theme.css:/home/marp/app/theme.css" `
        masterclass-slides slides.md --theme-set theme.css --pdf --allow-local-files -o slides.pdf

    if (-not $?) { exit 1 }
}
