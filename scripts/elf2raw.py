#!/usr/bin/env python3

import sys
from elftools.elf.elffile import ELFFile


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 elf2raw.py <OUT> <ELF>")
        exit(0)

    # コードが配置されているセグメントを取得
    ef = open(sys.argv[2], "rb")
    elffile = ELFFile(ef)
    t_segment = list(filter(
        lambda s: s.header["p_paddr"] == 0x20000000,
        elffile.iter_segments()
    ))[0]

    # RAWファイル書き出し
    with open(sys.argv[1], "wb") as of:
        of.write(t_segment.data())
        of.write(bytearray(0x200))

    ef.close()
