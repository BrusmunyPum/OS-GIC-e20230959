# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

- Student name/ID: PUM BRUSMUNY / e20230959
- Ubuntu username: gic-pum-brusmuny
- My values (`oslab values lab3`): name = ocean, tag = backup, v1 = 257, v2 = 346
- Files: `evidence/wildcards.txt`, `evidence/links.txt`, `evidence/replacement.txt`, `evidence/checkpoint.txt`, `evidence/plus.txt`, `evidence/challenge.txt`

## What I Saw

| State | What `cat` printed for the hard link | What `cat` printed for the symbolic link | What `readlink` printed |
|---|---|---|---|
| Before the rename | `version 257` | `version 257` | `ocean.txt` |
| After the rename, before the repair | `version 257` | `cat: ocean-soft.txt: No such file or directory` | `ocean.txt` |
| After a new file took the old name | `version 257` | `version 346` | `ocean.txt` |
| After my repair | `version 257` | `version 257` | `ocean-backup.txt` |

My repair (the two commands I wrote):
- `rm -- "$name-soft.txt"` (`rm -- ocean-soft.txt`)
- `ln -s "$name-$tag.txt" "$name-soft.txt"` (`ln -s ocean-backup.txt ocean-soft.txt`)

## Explanation

When a new `ocean.txt` holding `version 346` was created, it received a brand-new inode (`19141911`). Because the symbolic link `ocean-soft.txt` (inode `19141909`) only stores the path string `ocean.txt`, opening `ocean-soft.txt` resolved that path name to the new file and printed `version 346`. In contrast, the hard link `ocean-hard.txt` still pointed directly to the original file's inode (`19141756`), which had been renamed to `ocean-backup.txt`, so `ocean-hard.txt` continued to read `version 257`.

## What My Tests Do Not Prove

`cat` only proves what bytes are currently returned when reading a name, so it cannot prove whether two filenames share the same inode or are separate copies that happen to hold identical text. Only `ls -li` proves the underlying structure by showing inode numbers (`19141756` vs `19141911`), link counts, and symbolic link targets.

## Plus / Challenge (only if you did them)

- **Plus:** `notes/"$name"[12].txt` matched `ocean1.txt` and `ocean2.txt`, while `notes/"$name"[!1]*` matched `ocean2.txt` and `ocean.log` (because `.` is not `1` and `*` matched `log`, whereas `ocean12.txt` starts with `1` after `ocean`).
- **Challenge:** Starting with three hard links (`one.txt`, `two.txt`, `three.txt`), the link count dropped from `3` to `2` after `rm -- one.txt`, and from `2` to `1` after `rm -- two.txt`, while `"keep me"` stayed readable until the last hard link is deleted (link count `0`).

## AI Note (optional)

An AI tool explained keeping `?` outside double quotes in `notes/"$name"?.txt` so Bash still treats `?` as a one-character wildcard instead of literal text. I verified this by running the command in Core 1 and checking `evidence/wildcards.txt`, which matched only `ocean1.txt` and `ocean2.txt` (skipping `ocean12.txt`).
