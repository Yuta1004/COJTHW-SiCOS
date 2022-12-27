IMAGE := riscv-toolchain:rv32i

APP_NAME := fib

GCC := /opt/riscv/bin/riscv32-unknown-elf-gcc
ELF2RAW := /opt/scripts/elf2raw.py

fib.app: $(shell find . -name "*.c")
	make -C ../../kernel lib
	docker run -it -v $(CURDIR):/workdir/app -v $(CURDIR)/../../kernel/lib:/workdir/lib --rm $(IMAGE) bash -c " \
		cd /workdir/app && \
		$(GCC) \
			-o $(APP_NAME).elf \
			-I ../lib \
			-fpie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			start.s $^ ../lib/*.o && \
		$(ELF2RAW) \
			$(APP_NAME).app \
			$(APP_NAME).elf \
	"

clean:
	rm -f $(APP_NAME).app $(APP_NAME).elf

.PHONY: clean
