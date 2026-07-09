# C++ 20/23/26 Masterclass — slide deck renderer
# Thin wrapper around the official Marp CLI image so slide rendering follows
# the same "docker build once, docker run per lecture" pattern as docker/gcc
# and docker/clang.
FROM marpteam/marp-cli:latest

# The theme (theme.css) is deliberately built only on fonts already present
# in this image (Liberation Sans / Liberation Mono) - no font download at
# build time, so this Dockerfile has no network dependency beyond the base
# image pull itself.
