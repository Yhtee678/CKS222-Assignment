import pathlib
import subprocess
import sys

repo = pathlib.Path(sys.argv[1]).resolve()
exe = repo / "travelgo.exe"
base = pathlib.Path(__file__).resolve().parent / "traveler-tests"

# Use the first real record as the template so the format stays unchanged
first = (repo / "users.txt").read_bytes().splitlines(keepends=True)[0]
stripped = first.rstrip(b"\r\n")
eol = first[len(stripped):] or b"\n"
fields = stripped.split(b"\t")

def make_users(n):
    lines = []
    for i in range(1, n + 1):
        f = list(fields)
        f[0] = f"U{i:04d}".encode()
        lines.append(b"\t".join(f) + eol)
    return b"".join(lines)

cases = [
    ("T1", 100, "100 travelers, should load within capacity"),
    ("T2", 101, "101 travelers, should show capacity warning"),
    ("T3", 101, "101 travelers + Save & Exit, file must not be overwritten"),
]

for name, count, desc in cases:
    d = base / name
    d.mkdir(parents=True, exist_ok=True)
    data = make_users(count)
    (d / "users.txt").write_bytes(data)
    (d / "reviews.txt").write_bytes(b"")  # empty but present

    r = subprocess.run([str(exe)], input="7\n", text=True,
                       capture_output=True, cwd=d, timeout=30)

    after = (d / "users.txt").read_bytes()
    print("=" * 50)
    print(f"{name}: {desc}")
    print(f"Records in test file : {count}")
    print(f"Exit code            : {r.returncode}")
    print("Program output:")
    print(r.stdout)
    print("users.txt unchanged  :", after == data)