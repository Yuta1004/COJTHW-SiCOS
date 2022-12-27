IMAGE := riscv-toolchain:rv32i

BIN := /opt/riscv/bin
GCC := $(BIN)/riscv32-unknown-elf-gcc

kernel.elf: $(shell find . -name "*.c")
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-o kernel.elf \
			-T lscript.ld \
			-no-pie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			start.s $^ \
	"

clean:
	rm -f *.elf

.PHONY: clean
