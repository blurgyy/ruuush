#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, p, rp, Case = 0;
double x1, x2, y1, y2, A, rec[maxn];
struct Segment{
    double l, r, h;
    int side;
    bool operator< (Segment a){
        return h < a.h;
    }
}seg[maxn];
struct SegTreeNode{
    int left, right;
    int lazy, cov;
    double sum;
    void upd(int val){
        cov += val;
        lazy = val;
        if(left == right)
            sum = rec[right] * (cov > 0);
    }
}Tree[maxn<<2];

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void PushDown(int nowNode){
    if(Tree[nowNode].lazy){
        int val = Tree[nowNode].lazy;
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = rp - 1, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left >= right){
        Tree[nowNode].lazy = Tree[nowNode].cov = 0;
        Tree[nowNode].sum = rec[right];
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void update(int uleft, int uright, int val, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        /****/
        Tree[nowNode].upd(val);
        return;
    }
    PushDown(nowNode);
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

int idx(double e){
    return bs(e, rec, 1, rp - 1);
}

void add_point(){
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y1, seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = y2, seg[p++].side = -1;
    rec[rp++] = x1, rec[rp++] = x2;
}

void init(){
    p = rp = 1;
    A = 0;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        for(int i = 0; i < n; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            add_point();
        }
        sort(seg + 1, seg + p);
        sort(rec + 1, rec + rp);
        rp = unique(rec + 1, rec + rp) - rec - 1;
        build();
        double prevh = seg[1].h;
        for(int i = 0; i < p; ++ i){
            int l = idx(seg[i].l), r = idx(seg[i].r);
            A += (seg[i].h - prevh) * Tree[1].sum;
            printf("sum = %f, ", Tree[1].sum);
            prevh = seg[i].h;
            printf("A = %f\n", A);
            update(l, r, seg[i].side);
        }
        printf("%f\n", A);
    }
    return 0;
}