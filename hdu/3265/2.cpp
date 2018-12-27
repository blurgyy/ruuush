//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define y1 yyyyyy
using namespace std;
typedef long long ll;
const ll maxn = 50010;

struct Segment{
    ll l, r, h;
    int side;
    bool operator< (Segment a){
        if(h == a.h)return side > a.side;
        return h < a.h;
    }
}seg[maxn<<3];
struct SegTreeNode{
    ll left, right, cnt;
    ll sum;
}Tree[maxn<<3];
int n, p;
ll x1, x2, x3, x4, y1, y2, y3, y4;
ll ans;

void PushUp(int nowNode){
    if(Tree[nowNode].cnt)Tree[nowNode].sum = Tree[nowNode].right + 1 - Tree[nowNode].left;
    else if(Tree[nowNode].left == Tree[nowNode].right)Tree[nowNode].sum = 0;
    else Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(ll left = 1, ll right = maxn, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].cnt = Tree[nowNode].sum = 0;
    if(left == right)return;
    int mid((left + right) >> 1);
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
}

void update(ll uleft, ll uright, int addVal, int nowNode = 1){
    ll left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].cnt += addVal;
        PushUp(nowNode);
        return;
    }
    ll mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, addVal, nowNode<<1);
    if(uright > mid)update(uleft, uright, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

void add_point(){
    ++ x1, ++ x2, ++ x3, ++ x4;
    ++ y1, ++ y2, ++ y3, ++ y4;
    /**
    2
    4
    3
    1
     1 3 4 2
    */
    seg[p].l = x1, seg[p].r = x3, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x3, seg[p].h = y2, seg[p++].side = -1;
    seg[p].l = x3, seg[p].r = x4, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x3, seg[p].r = x4, seg[p].h = y3, seg[p++].side = -1;
    seg[p].l = x3, seg[p].r = x4, seg[p].h = y4, seg[p++].side = 1;
    seg[p].l = x3, seg[p].r = x4, seg[p].h = y2, seg[p++].side = -1;
    seg[p].l = x4, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x4, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;
    /*seg[p].l = x1, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y3, seg[p++].side = -1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y4, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;
    seg[p].l = x1, seg[p].r = x3, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x3, seg[p].h = y2, seg[p++].side = -1;
    seg[p].l = x4, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x4, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;*/
    //top = max(top, max(x1, max(x2, max(x3, x4))));
}

void init(){
    p = 0;
    ans = 0;
    //top = -1;
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        while(n--){
            scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
            add_point();
        }
        sort(seg, seg + p);
        build();
        for(int i = 0; i < p; ++ i ){
            ll l = seg[i].l, r = seg[i].r;
            update(l, r-1, seg[i].side);
            ans += 1ll * (seg[i+1].h - seg[i].h) * Tree[1].sum;
        }
        printf("%lld\n", ans);
    }
    return 0;
}