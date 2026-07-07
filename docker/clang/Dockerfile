# C++ 20/23/26 Masterclass — Clang student environment
# Base: silkeh/clang, official LLVM release, Clang 21.1.8 on Debian 13 (trixie)
# Pinned to the numbered tag (not :latest) so rebuilds stay reproducible —
# bump to :22 once that tag is published on Docker Hub.
FROM silkeh/clang:21

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        git \
        gdb \
        lldb \
        cppcheck \
        catch2 \
        libgtest-dev \
        pkg-config \
        less \
        vim \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash"]
