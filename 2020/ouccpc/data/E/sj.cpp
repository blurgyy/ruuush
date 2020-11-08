#include<bits/stdc++.h>

using namespace std;

int random(int x,int y){
    return rand()%(y-x+1)+x;
}

char s[100]={0},s2[100]={0};
bool f[100010];

const int maxo=100000,maxt=100000,maxa=100,maxh=100000000;

int main(){
    srand((int)time(NULL));
    for (int i=161;i<=170;i++){
        itoa(i,s,10);
        strcat(s,".in");
        memset(s2,0,sizeof(s2));
        strcat(s2,"./data/");
        strcat(s2,s);
        freopen(s2,"w",stdout);
        int o=random(1,maxo);
        int m=random(1,o);
        int n=o-m;
        printf("%d %d\n",n,m);
        for (int i=1;i<=100000;i++){
            f[i]=true;
        }
        for (int i=1;i<=n;i++){
            int t,a,h;
            t=random(1,maxt);
            while (!f[t]){
                t=random(1,maxt);
            }
            a=random(1,maxa);
            h=random(1,maxh);
            printf("%d %d %d\n",t,a,h);
            f[t]=false;
        }
        for (int i=1;i<=100000;i++){
            f[i]=true;
        }
        for (int i=1;i<=m;i++){
            int t,h;
            t=random(1,maxt);
            while (!f[t]){
                t=random(1,maxt);
            }
            h=random(1,maxh);
            printf("%d %d\n",t,h);
            f[t]=false;
        }
        fclose(stdout);
    }
    return 0;
}
