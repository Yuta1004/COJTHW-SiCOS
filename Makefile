IMAGE := riscv-toolchain:rv32i

OBJDUMP := $(BIN)/riscv32-unknown-elf-objdump
RAW_GENERATOR := python3 /workdir/raw_generator.py

kernel.raw: $(shell find kernel -name "*.c")
	make -C kernel kernel.elf
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c "\
		$(RAW_GENERATOR) \
			kernel.raw \
			kernel/kernel.elf \
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
	rm -f *.raw
	make -C kernel clean

.PHONY: kernel.raw, objdump, clean
