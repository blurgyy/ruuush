from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    n=int(1e5);
    F.write("%d\n"%(n));
    for i in range(n):
        F.write("%d %d\n"%(randint(1,int(1e9)),randint(1,int(1e9))));
    F.close()
for i in range(1,11):
    Gen(i)