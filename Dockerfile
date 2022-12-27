FROM ubuntu:22.04

WORKDIR /workdir

# Setup libraries
RUN apt update -y && \
    apt install -y \
        git python3 python3-pip \
        autoconf automake autotools-dev curl python3 \
        libmpc-dev libmpfr-dev libgmp-dev gawk build-essential \
        bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

# Setup RISC-V ToolChain
RUN git clone https://github.com/riscv/riscv-gnu-toolchain && \
    cd riscv-gnu-toolchain && \
    ./configure --prefix=/opt/riscv --with-arch=rv32i --with-abi=ilp32 && \
    make

# Setup Python Env
COPY ./scripts/* /opt/scripts/

RUN pip3 install pyelftools && \
    sed -i "s/\r//g" /opt/scripts/* && \
    chmod +x /opt/scripts/*
