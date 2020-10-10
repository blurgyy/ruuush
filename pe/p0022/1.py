#!/usr/bin/env -S python3 -u

fname = "names.txt"

with open(fname, 'r') as f:
    names = sorted(f.read().strip().replace('"', '').split(','))

tot = 0
for i in range(len(names)):
    names[i] = names[i].strip()
    score = 0
    for ch in names[i]:
        score += ord(ch) - ord('A') + 1
    print(f"{i+1}: '{names[i]}' --- {score}")
    tot += score * (i + 1)
print(tot)

# Author: Blurgy <gy@blurgy.xyz>
# Date:   Sep 24 2020
