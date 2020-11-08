from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    n=randint(1,100)
    k=randint(0,10)
    t=randint(1,min(10,n))
    F.write("%d %d %d\n"%(n,k,t));
    for i in range(n):
        F.write("%d"%(randint(0,1)));
    F.write("\n");
    F.close()
for i in range(33,41):
    Gen(i)
