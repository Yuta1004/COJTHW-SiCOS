IMAGE := riscv-toolchain:rv32i

ELF2RAW := python3 /workdir/scripts/elf2raw.py
FSRAW := python3 /workdir/scripts/fsraw.py

all:
	make kernel.raw
	make fs.raw

kernel.raw: $(shell find kernel -name "*.c")
	make -C kernel kernel.elf
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c "\
		$(ELF2RAW) \
			kernel.raw \
			kernel/kernel.elf \
	"

fs.raw: $(shell find fs -name "*")
	mkdir -p fs
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c "\
		$(FSRAW) \
			fs.raw \
			fs/* fs/**/* \
	"

run-shell:
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE)

build-image:
	docker build -t $(IMAGE) .

clean:
	rm -f *.raw
	make -C kernel clean

.PHONY: kernel.raw, fs.raw, run-shell, build-image, clean
