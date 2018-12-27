#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50010<<2;

struct Segment{
    ll l, r, h;
    int side;
    bool operator< (Segment a){
        return h < a.h;
    }
}seg[maxn];
struct SegTreeNode{
    int left, right, cnt;
    ll sum;
}Tree[maxn];
int n, p, rp, rec[maxn];
ll ans;
int x1, x2, x3, x4, y1, y2, y3, y4;

void PushUp(int nowNode){
    //if(Tree[nowNode].cnt)Tree[nowNode].sum = rec[Tree[nowNode].right+1] - rec[Tree[nowNode].left];
    if(Tree[nowNode].cnt > 0)Tree[nowNode].sum = Tree[nowNode].right - Tree[nowNode].left + 1;
    else if(Tree[nowNode].left == Tree[nowNode].right)Tree[nowNode].sum = 0;
    else Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(int left = 1, int right = rec[rp-1] - 1, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    //printf("building: l = %d, r = %d\n", left, right);
    Tree[nowNode].cnt = 0;
    Tree[nowNode].sum = 0;
    if(left == right)return;
    int mid((left + right) >> 1);
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
}

void update(int uleft, int uright, int addval, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].cnt += addval;
        PushUp(nowNode);
        return;
    }
    int mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, addval, nowNode<<1);
    if(uright > mid)update(uleft, uright, addval, nowNode<<1|1);
    PushUp(nowNode);
}

void add_point(){
    ++ x1, ++ x2, ++ x3, ++ x4;
    ++ y1, ++ y2, ++ y3, ++ y4;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y3, seg[p++].side = -1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y4, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;
    seg[p].l = x1, seg[p].r = x3, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x3, seg[p].h = y2, seg[p++].side = -1;
    seg[p].l = x4, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x4, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;
    rec[rp++] = x1, rec[rp++] = x2, rec[rp++] = x3, rec[rp++] = x4;
}
/*
int bs(int e, int arr[], int left, int right){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int idx(int e){
    return bs(e, rec, 1, rp-1);
}
*/
void init(){
    p = rp = 1;
    ans = 0;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        while(n--){
            scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
            add_point();
        }
        sort(seg + 1, seg + p);
        sort(rec + 1, rec + rp);
        rp = unique(rec + 1, rec + rp) - rec;
        build();
        for(int i = 1; i < p; ++ i){
            //int l = idx(seg[i].l), r = idx(seg[i].r);
            int l = seg[i].l, r = seg[i].r;
            update(l, r-1, seg[i].side);
            ans += (seg[i+1].h - seg[i].h) * Tree[1].sum;
            printf("l = %d, r = %d, (%d), Tree[1].sum = %d, ", l, r, seg[i].side, Tree[1].sum);
            printf("addv = %lld\n", (seg[i+1].h - seg[i].h) * Tree[1].sum);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

/**

2       
4       
3       
1       
 1 3 4 2
*/