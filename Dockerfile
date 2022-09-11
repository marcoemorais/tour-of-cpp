# Official gcc container provides build toolchain.
FROM gcc:10.4

LABEL maintainer="Marco Morais <marcoemorais@yahoo.com>"

# Base system including toolchain and dependencies.
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    cmake \
    git \
    less \
    pandoc \
    tree \
    valgrind

# Use the gcc toolchain by setting CC and CXX environment variables.
ENV CC=/usr/local/bin/gcc
ENV CXX=/usr/local/bin/g++

# Installation prefix for third party libraries.
ARG PREFIX_DIRECTORY=/usr/local

# Unit test.
ARG DOCTEST_TAG=v2.4.9
RUN git clone -q https://github.com/onqtam/doctest.git /doctest-${DOCTEST_TAG} --branch ${DOCTEST_TAG} \
    && mkdir -p /doctest-${DOCTEST_TAG}/.build \
    && cd /doctest-${DOCTEST_TAG}/.build \
    && cmake \
        -DCMAKE_BUILD_TYPE=RELEASE \
        -DCMAKE_INSTALL_PREFIX=${PREFIX_DIRECTORY} \
        .. \
    && make install \
    && rm -rf /doctest-${DOCTEST_TAG}

# By convention, all development in /src.
WORKDIR /src
