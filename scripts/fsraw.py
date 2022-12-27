import os
import sys
import glob

packaged_fnames = []

def packaging(of, f, permission, fname, fsize):
    global packaged_fnames

    # 権限チェック
    if permission <= 0 or permission > 7:
        print("ERROR: File's permission is wrong. (", permission, fname, ")")
        return

    # ファイル名重複チェック
    if fname in packaged_fnames:
        print("ERROR: Found name duplication. (", fname, ")")
        return
    packaged_fnames.append(fname)

    # ファイル名長さチェック
    if len(fname) > 11:
        print("ERROR: File name length is must be shorter than 11.")
        return

    # マジックナンバー, 権限
    of.write(0x410412.to_bytes(3, "little"))
    of.write((permission & 0b111).to_bytes(1, "little"))

    # ファイル名
    of.write(bytes(fname, "ascii"))
    of.write(0x00.to_bytes(12 - len(fname), "little"))

    # ファイルサイズ
    of.write(fsize.to_bytes(4, "little"))

    # 予約領域確保
    of.write(0x00.to_bytes(4, "little"))

    # ファイル本体
    of.write(f.read())

    # アライメント
    wrote_size = 0x18 + fsize
    alignment_size = 4096 * (wrote_size // 4096 + 1) - wrote_size
    of.write(0b00.to_bytes(alignment_size, "little"))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 fsraw.py <OUT> <FILE> ...")
        exit(0)

    of = open(sys.argv[1], "wb")

    for fpreq in sys.argv[2:]:
        for fpath in glob.glob(fpreq):
            print("Packaging", fpath, end="\t... ")
            with open(fpath, "rb") as f:
                permission = 0b101
                fname = fpath.split("/")[-1]
                fsize = os.path.getsize(fpath)
                packaging(of, f, permission, fname, fsize)
            print("OK")

    of.close()
