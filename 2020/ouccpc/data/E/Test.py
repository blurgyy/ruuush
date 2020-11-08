import os
from time import *
os.system("g++ 1.cpp -o 1")
os.system("g++ 2.cpp -o 2")
L=os.listdir("./data")
for i in L:
    os.system('1 <./data/'+i+'> ./out1/'+i.replace('in','out'));
    os.system('2 <./data/'+i+'> ./out2/'+i.replace('in','out'));
L=os.listdir('./out1')
for i in L:
   os.system('fc \"out1\\'+i+'\" \"out2\\'+i+'\"')
os.system("pause")
