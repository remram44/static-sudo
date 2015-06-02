#!/bin/sh

cd "$(dirname "$0")"
gcc -static -W -Wall -Wextra -Werror -pedantic rpzsudo.c -o rpzsudo-$(uname -m)
