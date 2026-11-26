
import pathlib
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parent.parent

if len(sys.argv) != 2:
    sys.exit(
        "Usage: python tests/test_traveler_capacity.py <executable>"
    )

exe = pathlib.Path(sys.argv[1]).resolve()

if not exe.is_file():
    sys.exit(f"Executable not found: {exe}")

first = (ROOT / "data" / "users.txt").read_bytes().splitlines()[0]
fields = first.split(b"\t")


def make_users(count):
    records = []

    for i in range(1, count + 1):
        record = list(fields)
        record[0] = f"U{i:04d}".encode()
        records.append(b"\t".join(record) + b"\n")

    return b"".join(records)


cases = [
    ("T1", 100, "Load travelers within capacity"),
    ("T2", 101, "Reject traveler capacity overflow"),
]

for name, count, description in cases:

    with tempfile.TemporaryDirectory() as temp:
        workdir = pathlib.Path(temp)
        data_dir = workdir / "data"
        data_dir.mkdir()

        users_data = make_users(count)
        reviews_data = b""

        users_file = data_dir / "users.txt"
        reviews_file = data_dir / "reviews.txt"

        users_file.write_bytes(users_data)
        reviews_file.write_bytes(reviews_data)

        result = subprocess.run(
            [str(exe)],
            input="7\n",
            text=True,
            capture_output=True,
            cwd=workdir,
            timeout=30
        )

        print("=" * 55)
        print(f"{name}: {description}")
        print(f"Traveler records: {count}")
        print(f"Exit code: {result.returncode}")
        print(result.stdout)

        if result.stderr:
            print(result.stderr)

        if count == 100:
            assert result.returncode == 0, (
                "100 travelers should load successfully"
            )

            assert "Loaded 100 travelers." in result.stdout

            assert (
                users_file.read_bytes().splitlines()
                == users_data.splitlines()
            ), "Traveler records must be preserved"

            assert reviews_file.read_bytes() == reviews_data

        else:
            assert result.returncode == 1, (
                "Traveler overflow must stop the program"
            )

            assert "Traveler capacity reached" in result.stdout

            assert users_file.read_bytes() == users_data, (
                "Overflow must not overwrite users.txt"
            )

            assert reviews_file.read_bytes() == reviews_data, (
                "Overflow must not overwrite reviews.txt"
            )

        print(f"{name}: PASSED")

print("All traveler capacity tests passed!")
