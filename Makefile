IMAGE := riscv-toolchain:rv32i

ELF2RAW := python3 /workdir/scripts/elf2raw.py
FSRAW := python3 /workdir/scripts/fsraw.py

all:
	make -C kernel
	cp kernel/kernel.raw .
	make -C fs
	cp fs/fs.raw .

run-shell:
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE)

build-image:
	docker build -t $(IMAGE) .

clean:
	rm -f *.raw
	make -C kernel clean
	make -C fs clean
	make -C apps clean

.PHONY: kernel.raw, fs.raw, run-shell, build-image, clean
