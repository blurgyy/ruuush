//#include<bits/stdc++.h>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1010;

struct Segment{
    double l, r, h;
    int side;
    bool operator< (Segment a){
        return h < a.h;
    }
}seg[maxn];
struct SegTreeNode{
    int left, right, cnt;
    double sum;
}Tree[maxn];
int n, p, rp, Case = 0;
double x1, x2, y1, y2, A, rec[maxn];

void PushUp(int nowNode){
    if(Tree[nowNode].cnt)Tree[nowNode].sum = rec[Tree[nowNode].right+1] - rec[Tree[nowNode].left];
    else if(Tree[nowNode].left == Tree[nowNode].right)Tree[nowNode].sum = 0;
    else Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(int left = 1, int right = rp-2, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].sum = 0;
    Tree[nowNode].cnt = 0;
    if(left == right)return;
    int mid = (left + right) >> 1;
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
}

void update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].cnt += addVal;
        PushUp(nowNode);
        return;
    }
    int mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, addVal, nowNode<<1);
    if(uright > mid)update(uleft, uright, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

int bs(double e, double arr[], int left, int right){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int idx(double a){
    return bs(a, rec, 1, rp-1);
}

void init(){
    A = 0;
    p = rp = 1;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        while(n--){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[p].l = x1, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
            seg[p].l = x1, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;
            rec[rp++] = x1, rec[rp++] = x2;
        }
        sort(seg + 1, seg + p);
        sort(rec + 1, rec + rp);
        rp = unique(rec + 1, rec + rp) - rec;
        build();
        double prevh = seg[1].h;
        for(int i = 1; i < p; ++ i){
            int l = idx(seg[i].l), r = idx(seg[i].r);
            A += (seg[i].h - prevh) * Tree[1].sum;
            prevh = seg[i].h;
            update(l, r-1, seg[i].side);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++ Case, A);
    }
    return 0;
}