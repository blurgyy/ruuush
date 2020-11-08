from random import*
def Gen(T):
    F=open("./data/"+str(T)+".in","w")
    n=500;m=500;T=100000;
    a=10;t=10;
    F.write("%d %d\n"%(n,m));
    A=list(range(1,T+1))
    shuffle(A);
    for i in range(n):
        F.write("%d %d %d\n"%(A[i],randint(1,a),randint(1,t)));
    shuffle(A);
    for i in range(m):
        F.write("%d %d\n"%(A[i],randint(1,t)));
    F.close()
for i in range(91,101):
    Gen(i)