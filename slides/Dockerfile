# C++ 20/23/26 Masterclass — slide deck renderer
# Thin wrapper around the official Marp CLI image so slide rendering follows
# the same "docker build once, docker run per lecture" pattern as docker/gcc
# and docker/clang.
FROM marpteam/marp-cli:latest

# Space Grotesk (display/headings) + JetBrains Mono (code/labels) - copied
# in from slides/fonts/ rather than fetched here, since this machine's
# network blocks outbound HTTPS to font CDNs during `docker build`. Installed
# as real system fonts (not @font-face) so font-family references resolve
# the same way in every render, independent of allow-local-files/CSP quirks.
COPY fonts/*.ttf /usr/share/fonts/truetype/masterclass/
RUN fc-cache -f
