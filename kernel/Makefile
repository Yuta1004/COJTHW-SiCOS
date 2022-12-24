IMAGE := riscv-toolchain:rv32i

IN_FILES := $(shell find . -name "*.c")
OUT_FILE := kernel.o

BIN := /opt/riscv/bin
GCC := $(BIN)/riscv32-unknown-elf-gcc

compile: $(IN_FILES)
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-c \
			-T $(LD_FILE) \
			-no-pie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			$(IN_FILES) \
	"
	mkdir -p ../obj/kernel
	mv *.o ../obj/kernel

.PHONY: compile
