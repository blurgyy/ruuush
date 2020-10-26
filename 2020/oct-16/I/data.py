#!/usr/bin/env -S python3 -u

from random import randint

T = 50
N = 50000
# T = 1
# N = 3

print(T)
for t in range(T):
    print(N)
    for n in range(N):
        print(randint(1, 2147483647), randint(1, 2147483647))

# Author: Blurgy <gy@blurgy.xyz>
# Date:   Oct 17 2020
