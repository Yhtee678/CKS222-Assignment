import pathlib
import subprocess
import sys
import tempfile

root = pathlib.Path(__file__).resolve().parent.parent

if len(sys.argv) < 2:
    print("Usage: python3 tests/test_persistence.py <executable>")
    sys.exit(2)

exe = pathlib.Path(sys.argv[1]).resolve()

if not exe.exists():
    print("Executable not found:", exe)
    sys.exit(2)

with tempfile.TemporaryDirectory() as temp:
    workdir = pathlib.Path(temp)

    filenames = ["users.txt", "reviews.txt"]
    before = {}

    for name in filenames:
        source = root / name
        content = source.read_bytes()
        before[name] = content
        (workdir / name).write_bytes(content)

    result = subprocess.run(
        [str(exe)],
        input="7\n",
        text=True,
        capture_output=True,
        cwd=workdir,
        timeout=30,
    )

    if result.returncode != 0:
        print(result.stdout)
        print(result.stderr)
        raise AssertionError(
            f"TravelGo exited with {result.returncode}"
        )

    for name in filenames:
        after = (workdir / name).read_bytes()

        if after != before[name]:
            raise AssertionError(
                f"{name} changed after Save & Exit"
            )

    print("Persistence smoke test passed!")