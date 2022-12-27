IMAGE := riscv-toolchain:rv32i

IN_FILES := $(shell find . -name "*.c")

BIN := /opt/riscv/bin
GCC := $(BIN)/riscv32-unknown-elf-gcc

kernel.elf: $(IN_FILES)
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-o kernel.elf \
			-T lscript.ld \
			-no-pie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			start.s $(IN_FILES) \
	"

clean:
	rm -f *.elf

.PHONY: clean
