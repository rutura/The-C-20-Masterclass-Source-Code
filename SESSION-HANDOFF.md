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

Still stale for GCC 16.2 (not edited, outside the "Clang only" request): "GCC 14" mentions and
old pasted output (sizes, `GNU 14.2.0`) in the "Environment 2: Windows, MinGW GCC" sections of
NOTES.md, and the `-lstdc++exp` comments in the `build-mingw-gcc.ps1` scripts ("GCC 14's
std::println needs..."). `-lstdc++exp` is still needed with GCC 16.2 on MinGW (the scripts pass).
