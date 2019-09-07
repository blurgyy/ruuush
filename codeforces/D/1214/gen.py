#!/usr/bin/python3

import random 

row = random.randint(1, 1000);
col = random.randint(3, 1000);
print(row, col);
for i in range(row):
	print("." * col);
