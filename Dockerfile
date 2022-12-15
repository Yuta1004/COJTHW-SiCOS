FROM ubuntu:22.04

WORKDIR /workdir

RUN apt update -y && \
    apt install -y \
        git autoconf automake autotools-dev curl python3 \
        libmpc-dev libmpfr-dev libgmp-dev gawk build-essential \
        bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev && \
    git clone https://github.com/riscv/riscv-gnu-toolchain && \
    cd riscv-gnu-toolchain && \
    ./configure --prefix=/opt/riscv --with-arch=rv32i --with-abi=ilp32 && \
    make
