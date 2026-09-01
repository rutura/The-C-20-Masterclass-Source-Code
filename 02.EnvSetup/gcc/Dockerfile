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
        curl \
        zip \
        unzip \
        tar \
    && rm -rf /var/lib/apt/lists/*

ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git ${VCPKG_ROOT} \
    && ${VCPKG_ROOT}/bootstrap-vcpkg.sh -disableMetrics
ENV PATH="${VCPKG_ROOT}:${PATH}"

WORKDIR /workspace

CMD ["bash"]