"""풀이 테스트 실행기 - test.cpp를 컴파일해서 실행한다.

사용법:
    python tools/test.py <문제 폴더>    # 한 문제
    python tools/test.py                # 레포의 모든 문제
"""
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TOOLS = ROOT / "tools"
BUILD = ROOT / "build"
FLAGS = ["-std=c++17", "-O2", "-Wall", "-Wextra"]


def display(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def run(problem_dir: Path) -> bool:
    print(f"== {display(problem_dir)}", flush=True)
    BUILD.mkdir(exist_ok=True)
    exe = BUILD / ("test.exe" if sys.platform == "win32" else "test")

    compiled = subprocess.run(["g++", *FLAGS, "-I", str(TOOLS), str(problem_dir / "test.cpp"), "-o", str(exe)])
    if compiled.returncode != 0:
        print("[COMPILE ERROR]")
        return False

    start = time.perf_counter()
    result = subprocess.run([str(exe)])
    print(f"({(time.perf_counter() - start) * 1000:.0f} ms)\n", flush=True)
    return result.returncode == 0


def main() -> int:
    if len(sys.argv) > 1:
        targets = [Path(sys.argv[1]).resolve()]
    else:
        targets = sorted(p.parent for p in ROOT.rglob("test.cpp") if TOOLS not in p.parents)
        if not targets:
            print("test.cpp가 있는 문제 폴더가 없습니다.")
            return 0

    failed = [d for d in targets if not run(d)]
    if len(targets) > 1:
        print(f"{len(targets) - len(failed)}/{len(targets)} passed")
        for d in failed:
            print(f"  - {display(d)}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
