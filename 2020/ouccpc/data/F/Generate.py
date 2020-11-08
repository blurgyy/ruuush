from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    T=100;
    F.write("%d\n"%(T));
    for i in range(T):
        F.write("%d\n"%(randint(1e8-100,1e8)));
    F.close()
for i in range(16,21):
    Gen(i)