from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    a=randint(2,4e4);
    k=a
    F.write("%d %d\n"%(a,k));
    F.close()
for i in range(31,41):
    Gen(i)