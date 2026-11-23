
import pathlib
import subprocess

# Locate the project and executable
repo = pathlib.Path(__file__).resolve().parent.parent
exe = repo / "travelgo.exe"

# Store temporary datasets inside the hotel test folder
base = pathlib.Path(__file__).resolve().parent / "hotel-tests"

# Read the first real traveler record as a template
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


def make_reviews(n):
    lines = []

    for i in range(1, n + 1):
        traveler_id = f"U{i:04d}"
        hotel_name = f"Hotel{i:03d}"

        review = (
            f"{traveler_id}\t5\tCapacity test review\t{hotel_name}\n"
        )
        lines.append(review.encode())

    return b"".join(lines)


cases = [
    ("H1", 50, "50 unique hotels, should load within capacity"),
    ("H2", 51, "51 unique hotels, should show capacity warning"),
    ("H3", 51, "51 unique hotels + Save & Exit, file must not be overwritten"),
]

for name, count, description in cases:
    folder = base / name
    folder.mkdir(parents=True, exist_ok=True)

    users_data = make_users(count)
    reviews_data = make_reviews(count)

    (folder / "users.txt").write_bytes(users_data)
    (folder / "reviews.txt").write_bytes(reviews_data)

    result = subprocess.run(
        [str(exe)],
        input="7\n",
        text=True,
        capture_output=True,
        cwd=folder,
        timeout=30
    )

    reviews_after = (folder / "reviews.txt").read_bytes()

    print("=" * 55)
    print(f"{name}: {description}")
    print(f"Unique hotels in test file: {count}")
    print(f"Exit code: {result.returncode}")
    print("Program output:")
    print(result.stdout)

    if result.stderr:
        print("Errors:")
        print(result.stderr)

    print("reviews.txt unchanged:", reviews_after == reviews_data)
