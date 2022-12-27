IMAGE := riscv-toolchain:rv32i

GCC := /opt/riscv/bin/riscv32-unknown-elf-gcc
ELF2RAW := /opt/scripts/elf2raw.py

kernel.raw: $(shell find . -name "*.c")
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-o kernel.elf \
			-T lscript.ld \
			-no-pie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			start.s $^ && \
		$(ELF2RAW) \
			kernel.raw \
			kernel.elf \
	"


lib: $(shell find lib -name "*.c")
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-c \
			-no-pie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			$^ \
	"
	mv *.o lib

clean:
	rm -f *.elf

.PHONY: clean
