#include<bits/stdc++.h>

using namespace std;

int n,m,o;
struct yl{
    int t,a,h;
} x[100010];
struct qlz{
    int t,h;
} y[100010];

bool cmp1(const yl a,const yl b){
    return a.t<b.t;
}

bool cmp2(const qlz a,const qlz b){
    return a.t<b.t;
}

bool check(int m){
    //printf("check %d\n",m);
    int i=1,j=1;
    int pret=1,nowi=1,nowj=1,nowih=x[i].h,nowjh=y[i].h;
    int nowt;
    int atkt;
    //printf("------%d\n",m);
    while (1){
        //printf("%d %d\n",x[i].t,y[j].t);
        //printf("--%d %d %d %d\n",nowi,nowj,i,j);
        nowt=min(x[i].t,y[j].t);
        //printf("%d %d %d %d\n",pret,nowt,nowi,nowih);
        while (nowi<i){
            atkt=min(nowih/m+(nowih%m==0?0:1),nowt-pret);
            nowih=nowih-m*atkt;
            pret=pret+atkt;
            if (pret>x[nowi].t+x[nowi].a) return false;
            if (nowih<=0) {nowi++; nowih=x[nowi].h;}
            if (pret==nowt) break;
        }
        //printf("%d %d %d %d\n",pret,nowt,nowi,nowih);
        if (nowj<j){
            atkt=min(nowjh/m+(nowjh%m==0?0:1),nowt-pret);
            nowjh=nowjh-m*atkt;
            pret=pret+atkt;
            if (nowjh<=0) {nowj++; nowjh=y[nowj].h;}
        }
        //printf("%d %d %d %d\n",pret,nowt,nowj,nowjh);
        if (nowt==2e8) return true;
        if (nowt==x[i].t){
            i++;
        }
        if (nowt==y[j].t){
            j++;
            if (j-nowj>=2){
                return false;
            }
        }
        pret=nowt;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    o=0;
    for (int i=1;i<=n;i++){
        scanf("%d%d%d",&x[i].t,&x[i].a,&x[i].h);
        o=max(o,x[i].h);
    }
    x[n+1].t=2e8;
    sort(x+1,x+n+1,cmp1);
    for (int i=1;i<=m;i++){
        scanf("%d%d",&y[i].t,&y[i].h);
        o=max(o,y[i].h);
    }
    sort(y+1,y+m+1,cmp2);
    y[m+1].t=2e8;
    int l=1;
    int r=o+1;
    while (l!=r){
        //printf("%d %d\n",l,r);
        int m=(l+r)/2;
        if (check(m)){
            r=m;
        } else {
            l=m+1;
        }
    }
    if (l==o+1){
        printf("impossible\n");
    } else printf("%d\n",l);
    return 0;
}
