#!/bin/sh
# Renders slides.pdf for every lecture folder that has a slides.md,
# using the masterclass-slides Docker image (see slides/README.md).
#
# Docker Desktop's -v mount needs a Windows drive-letter path, not the
# Git-Bash-style path $(pwd) resolves to on this machine - build one
# explicitly. Set WINROOT if the repo lives somewhere else.
#
# The lecture folder and slides/ (which holds theme.css) are mounted as
# siblings under /work rather than mounting theme.css directly inside the
# lecture folder - Marp CLI only resolves --theme-set files that live
# under its working directory, and mounting a single file straight into
# an already-mounted host folder makes Docker Desktop on Windows silently
# materialize an empty placeholder file back on the host. Mounting slides/
# itself as a read-only sibling avoids both problems. MSYS_NO_PATHCONV
# stops Git Bash from mangling the container's absolute -w path.
set -e

WINROOT="${WINROOT:-D:/Sandbox/The-C-20-Masterclass-Source-Code}"

if [ -z "$(docker images -q masterclass-slides 2>/dev/null)" ]; then
    docker build -t masterclass-slides slides
fi

find . -name "slides.md" -not -path "./slides/*" | while IFS= read -r md; do
    dir=$(dirname "$md")
    relpath=${dir#./}
    echo "=== $relpath ==="
    MSYS_NO_PATHCONV=1 docker run --rm \
        -v "$WINROOT/$relpath:/work/lecture" \
        -v "$WINROOT/slides:/work/slides:ro" \
        -w /work/lecture \
        masterclass-slides slides.md --theme-set /work/slides/theme.css --pdf --allow-local-files -o slides.pdf
done
