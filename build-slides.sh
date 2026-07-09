#!/bin/sh
# Renders slides.pdf for every lecture folder that has a slides.md,
# using the masterclass-slides Docker image (see slides/README.md).
#
# Docker Desktop's -v mount needs a Windows drive-letter path, not the
# Git-Bash-style path $(pwd) resolves to on this machine - build one
# explicitly. Set WINROOT if the repo lives somewhere else.
#
# The lecture folder and slides/ (which holds every theme-*.css) are
# mounted as siblings under /work rather than mounting theme files
# directly inside the lecture folder - Marp CLI only resolves --theme-set
# files that live under its working directory, and mounting a single file
# straight into an already-mounted host folder makes Docker Desktop on
# Windows silently materialize an empty placeholder file back on the host.
# Mounting slides/ itself as a read-only sibling avoids both problems.
# MSYS_NO_PATHCONV stops Git Bash from mangling the container's absolute
# -w path.
#
# Every theme-*.css in slides/ is registered with --theme-set on every
# render, so each lecture's slides.md picks its own look via its
# front-matter `theme:` field (masterclass / academic / editorial / linear
# / soft / contrast - see slides/README.md) without this script needing to
# know which lecture uses which theme.
set -e

WINROOT="${WINROOT:-D:/Sandbox/The-C-20-Masterclass-Source-Code}"

if [ -z "$(docker images -q masterclass-slides 2>/dev/null)" ]; then
    docker build -t masterclass-slides slides
fi

THEME_ARGS=""
for theme in slides/theme*.css; do
    THEME_ARGS="$THEME_ARGS --theme-set /work/slides/$(basename "$theme")"
done

find . -name "slides.md" -not -path "./slides/*" | while IFS= read -r md; do
    dir=$(dirname "$md")
    relpath=${dir#./}
    echo "=== $relpath ==="
    MSYS_NO_PATHCONV=1 docker run --rm \
        -v "$WINROOT/$relpath:/work/lecture" \
        -v "$WINROOT/slides:/work/slides:ro" \
        -w /work/lecture \
        masterclass-slides slides.md $THEME_ARGS --pdf --allow-local-files -o slides.pdf
done
