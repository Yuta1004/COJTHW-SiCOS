IMAGE := riscv-toolchain:rv32i

OUT_FILE := out.raw
LD_FILE := link_settings.ld

BIN := /opt/riscv/bin
GCC := $(BIN)/riscv32-unknown-elf-gcc
OBJDUMP := $(BIN)/riscv32-unknown-elf-objdump
RAW_GENERATOR := python3 /workdir/raw_generator.py

compile: src/*.c
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(GCC) \
			-o out.elf.tmp \
			-T $(LD_FILE) \
			-no-pie \
			-nostdlib \
			-static \
			start.s $^ && \
		$(RAW_GENERATOR) \
			$(OUT_FILE) \
			out.elf.tmp \
	"

objdump:
	make compile
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(OBJDUMP) \
			-d out.elf.tmp \
	"

run-shell:
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE)

build-image:
	docker build -t $(IMAGE) .

clean:
	rm *.raw *.tmp

.PHONY: compile, objdump, clean
