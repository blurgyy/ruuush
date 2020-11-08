from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")    
    for i in range(60):
        F.write("%d"%(randint(0,9)));
    F.write("\n");
    F.close()
for i in range(1,21):
    Gen(i)