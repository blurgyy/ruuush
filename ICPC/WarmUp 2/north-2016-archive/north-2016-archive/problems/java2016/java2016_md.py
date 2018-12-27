##################################################################
# ACM ICPC 2016-2017, NEERC                                      #
# Northern Subregional Contest                                   #
# St Petersburg, October 22, 2016                                #
##################################################################
# Problem J. Java2016                                            #
#                                                                #
# Original idea         Georgiy Korneev                          #
# Problem statement     Georgiy Korneev                          #
# Test set              Georgiy Korneev                          #
##################################################################
# Solution                                                       #
#                                                                #
# Author                Mikhail Dvorkin                          #
##################################################################

import sys
import os.path


filename = os.path.splitext(sys.argv[0])[0].split('_')[0]
with open(filename + '.in') as fin:
	n = int(fin.read())
v = ['?'] + [chr(ord('a') + i) for i in range(26)]
p = [v[i + 1] + '=' + v[i] + (' max ' if i < 12 else '+') + v[i] for i in range(20)]
p += ['+'.join([v[12 + i] for i in range(9) if (256 - n) & (1 << i)])]
with open(filename + '.out', 'w') as fout:
	fout.write('\n'.join(p))

