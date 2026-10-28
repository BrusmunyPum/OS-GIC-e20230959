# Lab 2 — Linux Navigation and File Management: individual report

Copy this template to `lab2/README.md` in your own course repository. Follow [the instructions](lab2-instruction.md). Your prediction, debrief and checkpoint answers are already saved by `oslab`; do not copy them here. The marks come from those records and your evidence files; this report is your own record of the lab.

- Student name/ID: PUM BRUSMUNY / e20230959
- Ubuntu username: gic-pum-brusmuny
- My values (`oslab values lab2`): file1 = `tax summary.txt`, file2 = `travel claims.txt`, owner = `Audit`, reader = `Marketing`, third = `Support`
- Files: `evidence/paths.txt`, `evidence/tree.txt`, `evidence/checkpoint.txt`, `evidence/plus.txt`, `evidence/challenge.txt`

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | `mv "tax summary.txt" ../reports/` | `/home/gic-pum-brusmuny/oslab-work/lab2/incoming` |
| Move the second file (absolute paths) | `mv "/home/gic-pum-brusmuny/oslab-work/lab2/incoming/travel claims.txt" "/home/gic-pum-brusmuny/oslab-work/lab2/reports/"` | `/home/gic-pum-brusmuny/oslab-work/lab2` |
| Read the report from my reader department (relative path) | `cat "../Audit/tax summary.txt"` | `/home/gic-pum-brusmuny/oslab-work/lab2/TechCorp/Marketing` |
| The path error I made on purpose, and its message | Command: `cat "reports/tax summary.txt"`<br>Error: `cat: 'reports/tax summary.txt': No such file or directory` | `/home/gic-pum-brusmuny/oslab-work/lab2/TechCorp/Marketing` |
| The relative path that fixed it | `../../reports/tax summary.txt` | `/home/gic-pum-brusmuny/oslab-work/lab2/TechCorp/Marketing` |

## Explanation

`oslab debrief lab2` records which prediction answers you confirmed and which you corrected. Here, in 3–5 sentences for yourself: why can a correct file name still give "No such file or directory"? What is the difference between `mv` and `cp`, using your own files as the example?

A correct file name can still cause "No such file or directory" because relative paths are resolved starting from the current working directory (`pwd`), not from where the file actually lives. When I was inside `TechCorp/Marketing`, the path `reports/tax summary.txt` failed because there is no `reports` folder inside `Marketing`; the path must first traverse up to the parent directory (`../../`) to locate `reports/`. The fundamental difference between `mv` and `cp` is that `cp` creates an independent duplicate of the file with a new inode and data blocks, whereas `mv` relocates or renames the directory entry without duplicating the file content. For instance, using `mv` on `tax summary.txt` moved it out of `incoming/` leaving `incoming/` empty, while using `cp` to copy `tax summary.txt` into `TechCorp/Audit/` kept the original copy intact inside `reports/`.

## What My Tests Do Not Prove

One or two sentences. Think about what `ls` shows and what `cmp` shows.

A directory listing (`ls`) only proves that directory entries with those names exist in the directory structure, but it cannot verify if the contents are intact or unaltered. In contrast, byte-by-byte comparison (`cmp`) proves that the data bytes are identical, but it does not test file permissions, timestamps, or whether user applications can correctly process the file contents.

## Plus / Challenge (only if you did them)

### Plus Task:
- **Move command from `mess/c`:** `mv "../a/b/lost file.txt" found.txt`
- **Copy command from `mess/a/b`:** `cp ../../c/found.txt ../../../TechCorp/Support/`
- **Number of `..` needed:** 2 to reach `found.txt` (`../../c/found.txt`) and 3 to reach `TechCorp/Support` (`../../../TechCorp/Support/`).

### Challenge Task:
- **Wildcard command:** `cp reports/*.txt TechCorp/Support/`
- **Quoting `*.txt`:** Fails with `No such file or directory` because quotes prevent shell globbing/expansion, treating `*.txt` as a literal file name.
- **`reports/.hidden.txt`:** Not copied because filenames beginning with a dot (`.`) are hidden files, which shell wildcard expansion (`*`) ignores by default.

## AI Note (optional)

One suggestion an AI tool gave you and the test you used to check it.

An AI tool suggested quoting file names containing spaces in double quotes (e.g., `"$file1"` instead of `'$file1'`) so that the shell variable expands properly without word-splitting. I verified this behavior by comparing `echo "$file1"` (which evaluated correctly to `tax summary.txt`) with `echo '$file1'` (which printed the literal string `$file1`).
