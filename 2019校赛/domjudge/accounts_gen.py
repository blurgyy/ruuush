#!/usr/bin/python

import random

def randchar():
	return random.choice("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm");
def randpasswd(length = 6):
	ret = ""
	for i in range(length):
		ret += randchar();
	return ret;

teamnames = [];
fname = "team.names";
with open(fname) as f:
	tmp = f.read().splitlines();
	for name in tmp:
		name = name.strip();
		if(len(name) == 0):
			continue;
		teamnames.append(name);

# for name in teamnames:
# 	print(name);

fname = "accounts.tsv";
with open(fname, 'w') as f:
	f.write("accounts\t1");

with open(fname, 'a') as f:
	for i in range(len(teamnames)):
		f.write("\nteam\t%s\tteam%02d\t%s" % (teamnames[i], i+1, randpasswd()));
