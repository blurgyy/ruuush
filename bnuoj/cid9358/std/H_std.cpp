#include<bits/stdc++.h>
using namespace std;
#define N 500010
#define ls(p) (p<<1)
#define rs(p) (p<<1 | 1)
const int INF=0x3f3f3f3f;
struct node {
    int l,r,cov,ans;
} t[N<<2];
char s[N];
int a[N],sum[N];
int n,m;
void push_up(int p) {
    t[p].ans=min(t[ls(p)].ans,t[rs(p)].ans);
}
void build(int p,int l,int r) {
    t[p].l=l;
    t[p].r=r;
    t[p].cov=0;
    if(l==r) {
        t[p].ans=sum[l];
        return;
    }
    int mid=l+r>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    push_up(p);
}
void update(int p,int y) {
    t[p].cov+=y;
    t[p].ans+=y;
}
void push_down(int p) {
    if(t[p].cov!=0) {
        update(ls(p),t[p].cov);
        update(rs(p),t[p].cov);
        t[p].cov=0;
    }
}
void change(int p,int l,int r,int y) {
    if(l<=t[p].l && t[p].r<=r) {
        update(p,y);
        return;
    }
    push_down(p);
    int mid=t[p].l+t[p].r>>1;
    if(l<=mid) change(ls(p),l,r,y);
    if(mid<r) change(rs(p),l,r,y);
    push_up(p);
}
int ask(int p,int x) {
    if(t[p].l==t[p].r)
        return t[p].ans;
    push_down(p);
    int mid=t[p].l+t[p].r>>1;
    if(x<=mid) return ask(ls(p),x);
    else return ask(rs(p),x);
}
int ask_first_less(int p,int x,int y) {
    if(x<=t[p].l) {
        if(t[p].ans>=y) return n+1;
        else {
            if(t[p].l==t[p].r) return t[p].l;
            else {
                push_down(p);
                if(t[ls(p)].ans<y) return ask_first_less(ls(p),x,y);
                else return ask_first_less(rs(p),x,y);
            }
        }
    }
    push_down(p);
    int mid=t[p].l+t[p].r>>1;
    if(x<=mid) {
        int lans=ask_first_less(ls(p),x,y);
        return (lans<=mid)?lans:ask_first_less(rs(p),x,y);
    }
    else return ask_first_less(rs(p),x,y);
}
int ask_last_equal(int p,int x,int y) {
    if(x<=t[p].l) {
        if(t[p].ans>y) return x-1;
        else {
            if(t[p].l==t[p].r) return t[p].l;
            else {
                push_down(p);
                if(t[rs(p)].ans==y) return ask_last_equal(rs(p),x,y);
                else return ask_last_equal(ls(p),x,y);
            }
        }
    }
    push_down(p);
    int mid=t[p].l+t[p].r>>1;
    if(x<=mid) {
        if(t[rs(p)].ans==y) return ask_last_equal(rs(p),x,y);
        else return ask_last_equal(ls(p),x,y);
    }
    else return ask_last_equal(rs(p),x,y);
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        assert(scanf("%d",&n)!=-1);
        assert(scanf("%d",&m)!=-1);
        assert(scanf("%s",s+1));
        for(int i=1; i<=n; ++i) {
            if(s[i]=='(') a[i]=1;
            else a[i]=-1;
            sum[i]=sum[i-1]+a[i];
        }
        build(1,1,n);
        while(m--) {
            int opt,x;
            assert(scanf("%d",&opt)!=-1);
            assert(scanf("%d",&x)!=-1);
            if(opt==1) {
                a[x]=-a[x];
                change(1,x,n,a[x]*2);
            }
            else {
                int y=(x>1)?ask(1,x-1):0;
                int pos=ask_first_less(1,x,y);
                if(pos<=n) printf("%d\n",pos-x);
                else printf("%d\n",ask_last_equal(1,x,y)-(x-1));
            }
        }
    }
    return 0;
}
