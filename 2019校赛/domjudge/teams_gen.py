#!/usr/bin/python

import random

teamnames = [];
fname = "team.names";
with open(fname) as f:
	tmp = f.read().splitlines();
	for name in tmp:
		name = name.strip();
		if(len(name) == 0):
			continue;
		teamnames.append(name);

fname = "teams.tsv";
with open(fname, 'w') as f:
	f.write("teams\t1");

with open(fname, 'a') as f:
	for i in range(len(teamnames)):
		f.write("\n%d\tteam%02d\t3\t%s" % (i+1, i+1, teamnames[i]));
