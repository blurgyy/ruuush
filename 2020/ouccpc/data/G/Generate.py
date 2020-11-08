from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    for i in range(5):
        F.write("%d"%(randint(0,9)))
    x=randint(0,5);
    y=randint(0,x);
    F.write(" %d %d\n"%(x,y))
    F.close()
for i in range(51,101):
    Gen(i)
