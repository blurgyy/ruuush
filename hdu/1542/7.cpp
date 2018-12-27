#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, p, rp, Case = 0;
double x1, x2, y1, y2, A, rec[maxn];
struct Segment{
    double l, r, h;
    int side;
}seg[maxn];
struct SegTreeNode{
    int left, right, cnt;
    double sum;
}Tree[maxn<<2];

bool operator< (Segment a, Segment b){
    return a.h < b.h;
}

void PushUp(int nowNode){
    if(Tree[nowNode].cnt)Tree[nowNode].sum = rec[Tree[nowNode].right+1] - rec[Tree[nowNode].left];
    else if(Tree[nowNode].left == Tree[nowNode].right)Tree[nowNode].sum = 0;
    else Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(int left = 1, int right = rp-2, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].cnt = 0;
    Tree[nowNode].sum = 0;
    if(left == right)return;
    int mid = (left + right) >> 1;
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    //PushUp(nowNode);
}

void update(int uleft, int uright, int val, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].cnt += val;
        PushUp(nowNode);
        return;
    }
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, val, nowNode<<1);
    if(uright > mid)update(uleft, uright, val, nowNode<<1|1);
    PushUp(nowNode);
}

int bs(double e, double arr[], int left, int right){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int idx(double x){
    return bs(x, rec, 1, rp-1);
}

void add_point(){
    seg[p].l = x1, seg[p].r = x2, seg[p].h = min(y1, y2), seg[p++].side = -1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = max(y1, y2), seg[p++].side = 1;
    rec[rp++] = x1, rec[rp++] = x2;
}

void init(){
    p = rp = 1;
    A = 0;
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            add_point();
        }
        sort(seg + 1, seg + p);
        sort(rec + 1, rec + rp);
        rp = unique(rec + 1, rec + rp) - rec;
        build();
        for(int i = 1; i < p; ++ i){
            int l = idx(seg[i].l), r = idx(seg[i].r);
            //printf("before upd: Tree[1].sum = %f\n", Tree[1].sum);
            update(l, r-1, seg[i].side);
            //printf("%f!, l = %f, r = %f, ", seg[i].h, seg[i].l, seg[i].r);
            A += (seg[i+1].h - seg[i].h) * Tree[1].sum;
            //printf("%f * %f = %f\n", seg[i+1].h - seg[i].h, Tree[1].sum, A);
            //prevh = seg[i].h;
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++ Case, A);
    }
    return 0;
}