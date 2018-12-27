#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50010;

struct Segment{
    ll l, r, h;
    int side;
    Segment(ll a = 0, ll b = 0, ll c = 0, int d = 0):l(a), r(b), h(c), side(d){}
    bool operator< (Segment a){
        return h < a.h;
    }
}seg[maxn<<2];
struct SegTreeNode{
    int left, right;
    ll cnt, sum;
}Tree[maxn<<3];
int n, p, top;
ll x1, x2, x3, x4, y1, y2, y3, y4;
ll ans;

void upd(int nowNode){
    if(Tree[nowNode].cnt)Tree[nowNode].sum = Tree[nowNode].right - Tree[nowNode].left + 1;
    else if(Tree[nowNode].left == Tree[nowNode].right)Tree[nowNode].sum = 0;
    else Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(int left = 1, int right = maxn, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].cnt = Tree[nowNode].sum = 0;
    if(left == right)return;
    int mid((left + right) >> 1);
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
}

void update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].cnt += addVal;
        upd(nowNode);
        return;
    }
    int mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, addVal, nowNode<<1);
    if(uright < mid)update(uleft, uright, addVal, nowNode<<1|1);
    upd(nowNode);
}

void init(){
    p = 0;
    ans = 0;
    top = 0;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        while(n--){
            scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
            /*
            2
            4
            3
            1
             1 3 4 2
            */
            ++ x1, ++ x2, ++ x3, ++ x4;
            ++ y1, ++ y2, ++ y3, ++ y4;
            seg[p++] = Segment(x1, x3, y1, 1);
            seg[p++] = Segment(x1, x3, y2, -1);
            seg[p++] = Segment(x3, x4, y1, 1);
            seg[p++] = Segment(x3, x4, y3, -1);
            seg[p++] = Segment(x3, x4, y4, 1);
            seg[p++] = Segment(x3, x4, y2, -1);
            seg[p++] = Segment(x4, x2, y1, 1);
            seg[p++] = Segment(x4, x2, y2, -1);
            top = max(top, (int)max(x1, max(x2, max(x3, x4))));
        }
        sort(seg, seg + p);
        build();
        for(int i = 0; i < p; ++ i){
            ll l = seg[1].l, r = seg[1].r;
            update(l, r, seg[i].side);
            ans += (seg[i+1].h - seg[i].h) * Tree[1].sum;
            printf("%lld\n", Tree[1].sum);
        }
        printf("%lld\n", ans);
    }
    return 0;
}