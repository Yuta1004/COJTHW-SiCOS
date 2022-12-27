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
        lambda s: s.header["p_type"] == "PT_LOAD",
        elffile.iter_segments()
    ))[0]

    # コードが配置されているアドレスを計算
    entry_addr = elffile.header.e_entry
    segment_addr = t_segment.header.p_paddr
    offset = entry_addr - segment_addr

    # RAWファイル書き出し
    with open(sys.argv[1], "wb") as of:
        of.write(t_segment.data()[offset:])
        of.write(bytearray(0x200))

    ef.close()
