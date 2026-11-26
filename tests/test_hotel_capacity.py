
import pathlib
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parent.parent

if len(sys.argv) != 2:
    sys.exit(
        "Usage: python tests/test_hotel_capacity.py <executable>"
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


def make_reviews(count):
    records = []

    for i in range(1, count + 1):
        traveler_id = f"U{i:04d}"
        hotel_name = f"Hotel{i:03d}"

        record = (
            f"{traveler_id}\t5\t"
            f"Capacity test review\t{hotel_name}\n"
        )

        records.append(record.encode())

    return b"".join(records)


cases = [
    ("H1", 50, "Load hotels within capacity"),
    ("H2", 51, "Reject hotel capacity overflow"),
]

for name, count, description in cases:

    with tempfile.TemporaryDirectory() as temp:
        workdir = pathlib.Path(temp)
        data_dir = workdir / "data"
        data_dir.mkdir()

        users_data = make_users(count)
        reviews_data = make_reviews(count)

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
        print(f"Unique hotels: {count}")
        print(f"Exit code: {result.returncode}")
        print(result.stdout)

        if result.stderr:
            print(result.stderr)

        if count == 50:
            assert result.returncode == 0, (
                "50 hotels should load successfully"
            )

            assert (
                "Loaded reviews and created 50 hotels."
                in result.stdout
            )

            assert (
                users_file.read_bytes().splitlines()
                == users_data.splitlines()
            ), "Traveler records must be preserved"

            assert (
                reviews_file.read_bytes().splitlines()
                == reviews_data.splitlines()
            ), "Review records must be preserved"

        else:
            assert result.returncode == 1, (
                "Hotel overflow must stop the program"
            )

            assert "Hotel capacity reached" in result.stdout

            assert users_file.read_bytes() == users_data, (
                "Overflow must not overwrite users.txt"
            )

            assert reviews_file.read_bytes() == reviews_data, (
                "Overflow must not overwrite reviews.txt"
            )

        print(f"{name}: PASSED")

print("All hotel capacity tests passed!")
