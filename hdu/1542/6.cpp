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
    int left, right, cnt, lazy;
    double sum;
    bool cov;
    void upd(int val){
        cnt += (right - left + 1) * val;
        lazy = val;
        if(left == right){
            sum = cnt ? rec[right] : 0;
        }
    }
}Tree[maxn<<2];

void PushUp(int nowNode){
    Tree[nowNode].cnt = Tree[nowNode<<1].cnt + Tree[nowNode<<1|1].cnt;
    Tree[nowNode].cov = Tree[nowNode<<1].cov && Tree[nowNode<<1|1].cov;
    if(Tree[nowNode].cov){
        A += Tree[nowNode].sum;
    }
}

void PushDown(int nowNode){
    int val = Tree[nowNode].lazy;
    if(val){
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = rp - 1, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].sum = rec[right] - rec[left];
    if(left == right){
        Tree[nowNode].cnt = 0;
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].upd(addVal);
        Tree[nowNode].cov = true;
        return;
    }
    int mid = (left + right) >> 1;
    PushDown(nowNode);
    if(uleft <= mid)update(uleft, uright, addVal, nowNode<<1);
    if(uright > mid)update(uleft, uright, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

double query(int qleft, int qright, int nowNode = 1){
    double ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(Tree[nowNode].cov){
        /*can't continue for fuck's sake*/
    }
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
    seg[p].l = x1, seg[p].r = x2, seg[p].h = min(y1, y2), seg[p++].side = 1;
    seg[p].l = x1, seg[p].r = x2, seg[p].h = max(y1, y2), seg[p++].side = -1;
    rec[rp++] = x1, rec[rp++] = x2;
}

void init(){
    p = rp = 1;
    A = 0;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            add_point();
        }
        sort(seg + 1, seg + p);
        sort(rec + 1, rec + rp);
        rp = unique(rec + 1, rec + rp) - rec - 1;
        build();
        double prevh = seg[1].h;
        for(int i = 1; i < p; ++ i){
            int l = idx(seg[i].l), r = idx(seg[i].r);
            A += (seg[i].h - prevh) * Tree[1].sum;
            printf("A = %f, Tree[1].sum = %f\n", A, Tree[1].sum);
            prevh = seg[i].h;
            update(l, r, seg[i].side);
        }
        printf("A = %f\n", A);
    }
    return 0;
}