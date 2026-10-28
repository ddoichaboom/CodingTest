"""프로그래머스 문제 폴더 생성기.

사용법:
    python tools/new.py <문제 번호 또는 URL> <섹션 폴더>
    예) python tools/new.py 1845 Programmers/Algorithm/01_Hash

<섹션 폴더>/<NN>_<문제명>/ 아래에 다음 파일을 만든다.
    README.md     풀이 기록 템플릿 + 문제 원문
    solution.cpp  C++ 시작 코드 (제출용)
    test.cpp      입출력 예로 채운 테스트
"""
import html
import re
import sys
import urllib.request
from datetime import date
from pathlib import Path
from string import Template

TEMPLATES = Path(__file__).resolve().parent / "templates"
LESSON_URL = "https://school.programmers.co.kr/learn/courses/30/lessons/{}"

SECTIONS = {
    "01_Hash": "해시",
    "02_StackQueue": "스택/큐",
    "03_Heap": "힙",
    "04_Sort": "정렬",
    "05_BruteForce": "완전탐색",
    "06_Greedy": "탐욕법",
    "07_DP": "동적계획법",
    "08_DFS_BFS": "DFS/BFS",
    "09_BinarySearch": "이분탐색",
    "10_Graph": "그래프",
}


def fetch(lesson_id: str) -> str:
    req = urllib.request.Request(LESSON_URL.format(lesson_id) + "?language=cpp", headers={"User-Agent": "Mozilla/5.0"})
    with urllib.request.urlopen(req, timeout=15) as res:
        return res.read().decode("utf-8")


def attr(page: str, name: str) -> str:
    m = re.search(rf'{name}="([^"]*)"', page)
    return html.unescape(m.group(1)) if m else ""


def inner_div(page: str, marker: str) -> str:
    """marker가 들어 있는 <div ...>의 내부 HTML을 중첩 div를 고려해 잘라낸다."""
    start = page.find(marker)
    if start < 0:
        return ""
    start = page.find(">", start) + 1
    depth = 1
    for m in re.finditer(r"<(/?)div\b", page[start:]):
        depth += -1 if m.group(1) else 1
        if depth == 0:
            return page[start:start + m.start()].strip()
    return ""


def flatten(statement: str) -> str:
    """<pre> 밖의 들여쓰기를 없앤다 - Markdown이 들여쓴 줄을 코드 블록으로 보지 않도록."""
    parts = re.split(r"(<pre.*?</pre>)", statement, flags=re.S)
    return "".join(p if p.startswith("<pre") else "\n".join(line.strip() for line in p.splitlines()) for p in parts)


def to_cpp(value: str) -> str:
    """입출력 예의 값 표기([1, 2], ["a"])를 C++ 중괄호 초기화로 바꾼다."""
    out, in_str, prev = [], False, ""
    for ch in value:
        if ch == '"' and prev != "\\":
            in_str = not in_str
        elif not in_str and ch == "[":
            ch = "{"
        elif not in_str and ch == "]":
            ch = "}"
        out.append(ch)
        prev = ch
    return "".join(out)


def text(cell: str) -> str:
    return html.unescape(re.sub(r"<[^>]+>", "", cell)).strip()


def examples(statement: str) -> str:
    pos = statement.find("입출력 예")
    table = re.search(r"<table.*?</table>", statement[pos:], re.S) if pos >= 0 else None
    if not table:
        return "    // 입출력 예를 찾지 못했습니다 - 직접 작성하세요"

    rows = re.findall(r"<tr>(.*?)</tr>", table.group(0), re.S)
    header = [text(c) for c in re.findall(r"<th[^>]*>(.*?)</th>", rows[0], re.S)] if rows else []
    lines = []
    for row in rows[1:]:
        cells = [text(c) for c in re.findall(r"<td[^>]*>(.*?)</td>", row, re.S)]
        if not cells or len(cells) != len(header):
            lines.append(f"    // 변환 실패한 행: {' | '.join(cells)}")
            continue
        args = ", ".join(to_cpp(c) for c in cells[:-1])
        lines.append(f"    CHECK(solution({args}), {to_cpp(cells[-1])});")
    return "\n".join(lines)


def next_index(section: Path) -> int:
    numbers = [int(m.group(1)) for d in section.iterdir() if d.is_dir() and (m := re.match(r"(\d+)_", d.name))]
    return max(numbers, default=0) + 1


def main() -> int:
    if len(sys.argv) != 3:
        print(__doc__)
        return 1

    m = re.search(r"(\d+)\D*$", sys.argv[1])
    if not m:
        print(f"문제 번호를 찾을 수 없습니다: {sys.argv[1]}")
        return 1
    lesson_id = m.group(1)
    section = Path(sys.argv[2])
    section.mkdir(parents=True, exist_ok=True)

    page = fetch(lesson_id)
    title = attr(page, "data-lesson-title")
    level = attr(page, "data-challenge-level")
    statement = inner_div(page, 'class="markdown')
    code = re.search(r"<textarea[^>]*>(.*?)</textarea>", page, re.S)
    if not (title and statement and code):
        print("문제 페이지에서 제목/본문/시작 코드를 찾지 못했습니다 - 페이지 구조가 바뀌었는지 확인하세요.")
        return 1

    safe_title = re.sub(r'[\\/:*?"<>|]', "", title).replace(" ", "_")
    target = section / f"{next_index(section):02d}_{safe_title}"
    target.mkdir()

    values = {
        "section": SECTIONS.get(section.name, section.name),
        "title": title,
        "level": level,
        "url": LESSON_URL.format(lesson_id),
        "date": date.today().isoformat(),
        "statement": flatten(statement),
        "code": html.unescape(code.group(1)).strip(),
        "examples": examples(statement),
    }
    for name in ("README.md", "solution.cpp", "test.cpp"):
        content = Template((TEMPLATES / name).read_text(encoding="utf-8")).safe_substitute(values)
        (target / name).write_text(content, encoding="utf-8", newline="\n")

    print(f"생성: {target}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
