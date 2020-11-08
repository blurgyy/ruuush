#include<bits/stdc++.h>

using namespace std;

char s[100];
int a,b,ta,tb;
int x[10],y[10],ans;

int main(){
    scanf("%s",s);
    scanf("%d%d",&a,&b);
    for (int i=0;i<=9;i++){
        x[i]=0;
    }
    for (int i=0;i<5;i++){
        x[s[i]-'0']++;
    }
    for (int i=0;i<=99999;i++){
        for (int j=0;j<=9;j++){
            y[j]=0;
        }
        int t=i;
        tb=0;
        for (int j=0;j<5;j++){
            tb+=((t%10==s[4-j]-'0')?1:0);
            y[t%10]++;
            t=t/10;
        }
        ta=0;
        for (int j=0;j<=9;j++){
            ta+=min(x[j],y[j]);
        }
        if (ta==a&&tb==b){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
