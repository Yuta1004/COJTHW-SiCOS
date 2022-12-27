IMAGE := riscv-toolchain:rv32i

OUT_FILE := kernel.raw
LD_FILE := link_settings.ld

BIN := /opt/riscv/bin
GCC := $(BIN)/riscv32-unknown-elf-gcc
OBJDUMP := $(BIN)/riscv32-unknown-elf-objdump
RAW_GENERATOR := python3 /workdir/raw_generator.py

compile:
	make clean
	make -C kernel
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-o kernel.elf \
			-T $(LD_FILE) \
			-no-pie \
			-nostdlib \
			-static \
			-falign-functions=1024 \
			start.s obj/**/*.o && \
		$(RAW_GENERATOR) \
			$(OUT_FILE) \
			kernel.elf \
	"

objdump:
	make compile
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(OBJDUMP) \
			-d kernel.elf \
	"

run-shell:
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE)

build-image:
	docker build -t $(IMAGE) .

clean:
	rm -f *.raw *.elf
	rm -rf obj

.PHONY: compile, objdump, clean
