IMAGE := riscv-toolchain:rv32i

OUT_FILE := myprogram
LD_FILE := link_settings.ld

BIN_PATH := /opt/riscv/bin
GCC := $(BIN_PATH)/riscv32-unknown-elf-gcc

compile: *.c
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) $(GCC) \
		-o $(OUT_FILE) \
		-T $(LD_FILE) \
		$^

build-image:
	docker build -t $(IMAGE) .
