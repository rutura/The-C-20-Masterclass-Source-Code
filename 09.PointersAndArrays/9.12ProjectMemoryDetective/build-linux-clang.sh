#!/bin/sh
# Answer key for the notes: the Memory Detective with Clang, in the Linux container.
# Run inside this folder. Same shape as the GCC script.

# No "set -e": the sanitizers stop each buggy case with a non-zero exit code,
# which is exactly what we want to see.

# Build 1: AddressSanitizer plus UndefinedBehaviorSanitizer.
echo "> clang++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o detective"
clang++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o detective || exit 1

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
