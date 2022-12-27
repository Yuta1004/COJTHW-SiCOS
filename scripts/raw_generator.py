import sys

from elftools.elf.elffile import ELFFile


def write_raw(out, body):
    with open(out, "wb") as f:
        f.write(body)
        f.write(bytearray(0x200))


def parse(out, f):
    elffile = ELFFile(f)
    for segment in elffile.iter_segments():
        if segment.header["p_paddr"] == 0x20000000:
            write_raw(out, segment.data())


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 raw_generator.py <OUT> <ELF>")
        exit(0)

    with open(sys.argv[2], "rb") as f:
        parse(sys.argv[1], f)
