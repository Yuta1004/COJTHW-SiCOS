IMAGE := riscv-toolchain:rv32i

IN_FILES := $(shell find obj -name "*.o")
OUT_FILE := out.raw
LD_FILE := link_settings.ld

BIN := /opt/riscv/bin
GCC := $(BIN)/riscv32-unknown-elf-gcc
OBJDUMP := $(BIN)/riscv32-unknown-elf-objdump
RAW_GENERATOR := python3 /workdir/raw_generator.py

compile:
	make -C kernel
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-o out.elf \
			-T $(LD_FILE) \
			-no-pie \
			-nostdlib \
			-static \
			start.s $(IN_FILES) && \
		$(RAW_GENERATOR) \
			$(OUT_FILE) \
			out.elf \
	"

objdump:
	make compile
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(OBJDUMP) \
			-d out.elf \
	"

run-shell:
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE)

build-image:
	docker build -t $(IMAGE) .

clean:
	rm *.raw *.elf

.PHONY: compile, objdump, clean
