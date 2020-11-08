#include<bits/stdc++.h>

using namespace std;

long long h=1e9+7;
int l,r;
long long ans;
int a[100],tot;

void get(int l,int r){
    if (l==r) return;
    int m=0;
    int j=tot;
    for (int i=tot;i>=1;i--){
        if (m+2*a[i]<=r) break;
        j=i;
        if (m+a[i]<=l&&m+2*a[i]>r){
            m=m+a[i];
        }
    }
    m=m+a[j];
    //printf("%d %d %d\n",l,r,m);
    int tl=l;
    int tr=r;
    for (int i=j;i>=1;i--){
        tl=tl%a[i];
        tr=tr%a[i];
        if (tl<=tr){
            break;
        }
    }
    ans=ans*(tr-tl+1)%h;
    //printf("%d %d %d %d %d %d\n",l,r,m,tl,tr,tr-tl+1);
    get(l,m-1);
    get(m,r);
}

int main(){
    scanf("%d%d",&l,&r);
    ans=1;
    int m;
    m=1;
    a[1]=1;
    tot=1;
    while (m<r) {
        m=m*2;
        tot++;
        a[tot]=m;
    }
    //printf("%d",tot);
    get(l,r);
    printf("%lld\n",ans);
    return 0;
}
