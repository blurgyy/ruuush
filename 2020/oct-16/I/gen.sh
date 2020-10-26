#!/usr/bin/env bash

mkdir -p bin data

# Compile source
if [[ ! -x ./bin/my ]]; then
    g++ 2.cpp -o ./bin/my
fi
if [[ ! -x ./bin/ac ]]; then
    g++ ac.cpp -o ./bin/ac
fi

# Generate data
python3 -u data.py > data/data.in

# test
bin/my < data/data.in > data/my.out
bin/ac < data/data.in > data/ac.out

# diff
diff data/{my,ac}.out

# Author: Blurgy <gy@blurgy.xyz>
# Date:   Oct 17 2020
