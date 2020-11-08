#include<bits/stdc++.h>

using namespace std;

int n,t,o,k;
int a[1000],b[1000],c[1000],tot,ans,tans;
bool f;

int main(){
    scanf("%d%d",&n,&k);
    tot=0;
    o=n;
    for (int i=2;i<=sqrt(n);i++){
        t=i;
        f=false;
        while (n%i==0){
            if (!f){
                f=true;
                tot++;
                a[tot]=i;
                b[tot]=0;
                c[tot]=1;
            }
            c[tot]=c[tot]*i;
            b[tot]++;
            n=n/i;
        }
    }
    if (n>=1){
        tot++;
        a[tot]=n;
        b[tot]=1;
        c[tot]=n;
    }
    /*
        for (int i=1;i<=tot;i++){
            printf("%d^%d\n",a[i],b[i]);
        }
    */
    ans=0;
    for (int i=1;i<=o/2;i++){
        if (i>=k) break;
        if (o%i==0){
            for (int j=1;j<=tot;j++){
                if (i%c[j]!=0&&i*a[j]>=k){
                    tans=0;
                    n=o/i;
                    for (int l=2;l<=sqrt(n);l++){
                        while (n%l==0){
                            n=n/l;
                            tans+=l;
                        }
                    }
                    if (n>1) tans+=n;
                    ans=max(tans,ans);
                }
            }
        }
    }
    printf("%d",ans);
    return 0;
}
