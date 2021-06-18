#!/bin/sh

cd "$(dirname "$0")"
musl-gcc -static \
    -Os -s \
    -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections \
    -fno-unwind-tables -fno-asynchronous-unwind-tables \
    -fno-math-errno -fno-unroll-loops -fmerge-all-constants \
    -fno-ident -Wl,-z,norelro \
    -W -Wall -Wextra -Werror -pedantic \
    rpzsudo.c \
    -o rpzsudo-$(uname -m)
strip -S --strip-unneeded rpzsudo-$(uname -m)
