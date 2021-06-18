#!/bin/sh

cd "$(dirname "$0")"
musl-gcc -static \
    -W -Wall -Wextra -Werror -pedantic \
    rpzsudo.c \
    -o rpzsudo-$(uname -m)
