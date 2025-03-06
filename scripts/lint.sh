#!/bin/sh

# Lint all (C++) files in the project,
# to run from the root of the project.
git ls-files \
    | grep -e '\.cpp$' -e '\.hpp$' -e '\.c$' -e '\.h$' \
    | xargs clang-tidy -extra-arg=-std=c++17
