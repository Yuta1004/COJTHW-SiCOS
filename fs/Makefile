IMAGE := riscv-toolchain:rv32i

FSRAW := /opt/scripts/fsraw.py

fs.raw: $(shell find entries -name "*") $(shell find ../apps -name "*.c")
	make -C ../apps
	cp ../apps/*.app entries
	docker run -it -v $(CURDIR):/workdir --rm $(IMAGE) bash -c " \
		$(FSRAW) \
			fs.raw \
			entries/* \
	"

clean:
	rm -f fs.raw

.PHONY: clean
