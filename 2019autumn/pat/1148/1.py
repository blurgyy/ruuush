#!/usr/bin/python3

import numpy as np
from numpy import random 

n = random.randint(5, 100+1);
say = np.arange(1, n+1);
arr = np.arange(1, n+1);
random.shuffle(arr);
ww = np.array([arr[0], arr[1]]);

say[ww[0]-1] *= -1;
say[ww[1]-1] *= -1;

say[ww[0]-1] *= -1;

x = random.randint(0, n+1);
while(x == ww[0]-1):
	x = random.randint(0, n);
say[x] *= -1;

with open("in.in", 'w') as f:
	f.write(str(n) + '\n');
	for i in say:
		f.write(str(i) + '\n');

print(ww)
