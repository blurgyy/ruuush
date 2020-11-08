from random import*

def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    r=randint(1e6-100,1e6);
    l=randint(0,100);
    F.write("%d %d\n"%(l,r));
    F.close()
for i in range(21,41):
    Gen(i)