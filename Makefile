IMAGE := riscv-toolchain:rv32i

OUT_FILE := out
LD_FILE := link_settings.ld

GCC := /opt/riscv/bin/riscv32-unknown-elf-gcc
RAW_GENERATOR := python3 /workdir/raw_generator.py

compile: *.c
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
			out.elf.tmp && \
		rm \
			out.elf.tmp \
	"

run-shell:
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE)

build-image:
	docker build -t $(IMAGE) .
