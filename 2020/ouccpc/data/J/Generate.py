from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    n=100000;
    F.write("%d\n"%n);
    for i in range(n-1):
        F.write("%d "%(100000000))
    F.write("%d\n"%(100000000))
    F.close()
for i in range(30,31):
    Gen(i)
