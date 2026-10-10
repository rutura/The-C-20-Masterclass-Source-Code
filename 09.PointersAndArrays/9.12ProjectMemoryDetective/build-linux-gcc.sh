#!/bin/sh
# Answer key for the notes: the Memory Detective with GCC, in the Linux container.
# Run inside this folder.

# No "set -e": the sanitizers stop each buggy case with a non-zero exit code,
# which is exactly what we want to see.

# Build 1: AddressSanitizer plus UndefinedBehaviorSanitizer.
#   -g                       file names and line numbers in the report
#   -fno-omit-frame-pointer  complete stack traces
echo "> g++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o detective"
g++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o detective || exit 1

for case in heap-overflow stack-overflow use-after-free double-free leak stale-pointer signed-overflow; do
    echo
    echo "=== $case"
    ./detective $case 2>&1 | head -8
done

echo
echo "=== fixed versions"
for case in heap-overflow stack-overflow use-after-free double-free leak stale-pointer signed-overflow; do
    ./detective $case fixed >/dev/null 2>&1
    echo "$case exit code $?"
done

# Optional: valgrind, a different tool that needs NO special build. It cannot
# run together with the sanitizers, so use a plain build.
#     apt-get install -y valgrind
echo
echo "=== valgrind (optional, plain build)"
if command -v valgrind >/dev/null 2>&1; then
    g++ -std=c++23 -g main.cpp -o detective_plain
    valgrind --leak-check=full ./detective_plain leak 2>&1 | grep -E "definitely lost|ERROR SUMMARY|at 0x|by 0x" | head -6
else
    echo "valgrind is not installed in this container (apt-get install -y valgrind)"
fi
