
import pathlib
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parent.parent
DATA_DIR = ROOT / "data"

if len(sys.argv) != 2:
    sys.exit(
        "Usage: python tests/test_persistence.py <executable>"
    )

exe = pathlib.Path(sys.argv[1]).resolve()

if not exe.is_file():
    sys.exit(f"Executable not found: {exe}")

with tempfile.TemporaryDirectory() as temp:
    workdir = pathlib.Path(temp)
    test_data = workdir / "data"
    test_data.mkdir()

    filenames = ["users.txt", "reviews.txt"]
    before = {}

    for name in filenames:
        content = (DATA_DIR / name).read_bytes()
        before[name] = content
        (test_data / name).write_bytes(content)

    result = subprocess.run(
        [str(exe)],
        input="7\n",
        text=True,
        capture_output=True,
        cwd=workdir,
        timeout=30
    )

    if result.returncode != 0:
        print(result.stdout)
        print(result.stderr)

        raise AssertionError(
            f"TravelGo exited with {result.returncode}"
        )

    for name in filenames:
        after = (test_data / name).read_bytes()

        if after != before[name]:
            raise AssertionError(
                f"{name} changed after Save and Exit"
            )

    print("Persistence smoke test passed!")
