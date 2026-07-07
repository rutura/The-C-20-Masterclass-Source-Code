# C++ 20/23/26 Masterclass — GCC student environment
# Base: official Docker Library image, GCC 16.1.0 on Debian 13 (trixie)
FROM gcc:16

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        git \
        gdb \
        clang-format \
        clang-tidy \
        cppcheck \
        catch2 \
        libgtest-dev \
        pkg-config \
        less \
        vim \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash"]
