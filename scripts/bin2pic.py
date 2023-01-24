import sys


def convert(of, rf, width, height):
    of.write(width.to_bytes(4, "little"))
    of.write(height.to_bytes(4, "little"))
    for _ in range(height):
        of.write(rf.read(width*4))
        of.write(0x00.to_bytes((1280-width)*4))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 bin2pic.py <FILE> <WIDTH> <HEIGHT> ...")
        exit(0)

    fname = "".join(sys.argv[1].split(".")[0:-1])
    width = int(sys.argv[2])
    height = int(sys.argv[3])

    if width > 1280:
        print("Error: Picture width is must be shorter than 1280.")
        exit(1)

    print("Converting", fname, end="\t... ")

    with open(fname+".pic", "wb") as of:
        with open(fname+".bin", "rb") as rf:
            convert(of, rf, width, height)

    print("OK")

