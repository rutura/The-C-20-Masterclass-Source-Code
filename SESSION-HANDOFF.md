# Session handoff

## 2026-10-24: MinGW upgrade, Clang link fix (chapter 7, lectures 7.12 to 7.15)

`C:\mingw64` was upgraded to Clang 23.1.3, GCC/libstdc++ 16.2.0, GNU ld 2.47 (Brecht Sanders r3).

Problem: `clang++ ... -lstdc++exp` with the default GNU `ld` prints about 24 lines of
`libstdc++exp.a(print.o): duplicate section ... has different size` (Clang-built objects
versus the GCC-built `print.o`). They are warnings (exit code 0, the exe runs), but they
look like a failure, and a script under `$ErrorActionPreference = 'Stop'` dies on them.
Dropping `-lstdc++exp` is not an option: `std::__open_terminal` stays undefined.

Fix: link with Clang's own linker, `-fuse-ld=lld -lstdc++exp`, on the link command of any
program that uses `std::println`. lld ignores library order, so 7.13 step 4b ("library before
the object") now uses `-fuse-ld=ld` explicitly and no `-lstdc++exp`.

Changed:
- `7.12`, `7.13`, `7.14` `build-mingw-clang.ps1`
- `7.15ProjectCMakeCommandLine/CMakeLists.txt` (`target_link_options(rooster PRIVATE -fuse-ld=lld)` for Clang on Windows)
- `07.PracticalBuiltInFeatures/NOTES.md`, the four "Environment 3: Windows, MinGW Clang" sections
  (versions, gotcha box, commands, pasted outputs from real runs), plus the two summary lines.

Verified: all four `build-mingw-clang.ps1` scripts exit 0; the 7.14 by-hand DLL steps match the notes.
All four `build-mingw-gcc.ps1` scripts also still exit 0 with GCC 16.2.

### Follow-up: MinGW GCC sections refreshed for GCC 16.2.0

Every command of the four "Environment 2: Windows, MinGW GCC" sections was run for real
(scratch copies in `D:\Sandbox\_build\gcc-test`). Findings:
- `-lstdc++exp` is still required with MinGW GCC 16.2 (without it: undefined `std::__open_terminal`
  and `std::__write_to_terminal`). GNU ld has no duplicate-section problem with GCC objects, so GCC
  needs no `-fuse-ld=lld`, and the "library after the objects" rule still holds for GNU ld.
- The old claim "newer compilers like GCC 16 do not need it" was wrong for MinGW; reworded in 7.12 and in the
  Linux GCC note.
- Updated from the real runs: version banners (r3, 16.2.0; cmake 4.4.4, ninja 1.13.2), exe start address,
  object/exe/DLL/archive sizes, `ar tv` sizes and date, DLL export RVA, `.text+0x..` offsets in the
  undefined-reference lines, the "about N KB" prose, and the `build-mingw-gcc.ps1` comments (7.12, 7.13).
- Unchanged because the real output matched: `nm`/`objdump -f` object output, mangled names, error message formats,
  install layouts, CMake `--verbose` command shapes.

Left alone on purpose: "GCC 14.2.0" in the Linux Docker part of 7.15 (Debian's `g++-14` in the image, not MinGW).

All eight `build-mingw-{gcc,clang}.ps1` scripts exit 0, and every size they print appears in NOTES.md.
