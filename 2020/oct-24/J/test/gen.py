#!/usr/bin/env -S python3 -u

import random

# T = 100000
T = 5
n = 1000000

print(T)
for _ in range(T):
    print(n)
    fa = [random.randint(1, _) for _ in range(2, n + 1)]
    print(*fa)

# Author: Blurgy <gy@blurgy.xyz>
# Date:   Oct 24 2020
