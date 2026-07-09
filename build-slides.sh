#!/bin/sh
# Renders slides.pdf for every lecture folder that has a slides.md,
# using the masterclass-slides Docker image (see slides/README.md).
#
# Docker Desktop's -v mount needs a Windows drive-letter path, not the
# Git-Bash-style path $(pwd) resolves to on this machine - build one
# explicitly. Set WINROOT if the repo lives somewhere else.
set -e

WINROOT="${WINROOT:-D:/Sandbox/The-C-20-Masterclass-Source-Code}"

if [ -z "$(docker images -q masterclass-slides 2>/dev/null)" ]; then
    docker build -t masterclass-slides slides
fi

find . -name "slides.md" -not -path "./slides/*" | while IFS= read -r md; do
    dir=$(dirname "$md")
    relpath=${dir#./}
    echo "=== $relpath ==="
    docker run --rm \
        -v "$WINROOT/$relpath:/home/marp/app" \
        -v "$WINROOT/slides/theme.css:/home/marp/app/theme.css" \
        masterclass-slides slides.md --theme-set theme.css --pdf --allow-local-files -o slides.pdf
done
