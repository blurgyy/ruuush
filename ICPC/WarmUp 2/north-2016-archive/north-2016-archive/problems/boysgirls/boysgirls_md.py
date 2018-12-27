##################################################################
# ACM ICPC 2016-2017, NEERC                                      #
# Northern Subregional Contest                                   #
# St Petersburg, October 22, 2016                                #
##################################################################
# Problem B. Boys and Girls                                      #
#                                                                #
# Original idea         Pavel Mavrin                             #
# Problem statement     Pavel Mavrin                             #
# Test set              Pavel Mavrin                             #
##################################################################
# Solution                                                       #
#                                                                #
# Author                Mikhail Dvorkin                          #
##################################################################

import sys
import os.path


def cycle(n, x, y):
	c, d = 'GB'
	if x < y:
		c, d, x, y = d, c, y, x
	if (x, y) == (n, 0):
		return c * x
	s = c * (x + 1) + d * (y + 1)
	s += (n - len(s)) // 2 * (c + d)
	if len(s) == n and y >= 0:
		return s

def solve(n, x, y):
	m = n // 2
	if n % 2:
		s = cycle(n, x, y)
		return mix(s[m:], s[:m] + '_')[:n] if s else None
	a, b = x // 2, y // 2
	if (a + b + m) % 2:
		if a > b:
			a += 1
		else:
			b += 1
	if x >= m:
		a, b = m, 0
	if y >= m:
		a, b = 0, m
	return mix(cycle(m, a, b), cycle(m, x - a, y - b))

def mix(s, t):
	if s and t:
		return ''.join([x + y for x, y in zip(s, t)])


filename = os.path.splitext(sys.argv[0])[0].split('_')[0]
with open(filename + '.in') as fin:
	n, x, y = map(int, fin.read().split())
s = solve(n, n - x, n - y)
with open(filename + '.out', 'w') as fout:
	fout.write(s if s else "Impossible")

