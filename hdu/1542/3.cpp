//IDIOT

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Segment{
    double l, r, h;
    int side;
}seg[maxn];
struct SegTree{
    int left, right;
    bool cov;
    double sum;
}Tree[maxn<<2];
int n, p, rp, Case = 0;
double x1, x2, y1, y2, A, rec[maxn];

void PushUp(int nowNode){
    Tree[nowNode].sum = (Tree[nowNode<<1].cov * Tree[nowNode<<1].sum + Tree[nowNode<<1|1].cov * Tree[nowNode<<1|1].sum);
    //Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
    Tree[nowNode].cov = Tree[nowNode<<1].cov || Tree[nowNode<<1|1].sum;
}

void PushDown(int nowNode){
    Tree[nowNode<<1].cov = Tree[nowNode<<1|1].cov = Tree[nowNode].cov;
}

void build(int left = 1, int right = rp-1, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    //printf("building: %f(%d) to %f(%d)\n", rec[left], left, rec[right], right);
    if(left >= right){
        Tree[nowNode].cov = false;
        Tree[nowNode].sum = rec[right];
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    PushUp(nowNode);
}

void update(int uleft, int uright, bool upd, int nowNode = 1){///upd: 0 for minus, 1 for add
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].cov = upd;
        return;
    }
    PushDown(nowNode);
    printf("from %f to %f is %s.\n", rec[left], rec[right], upd ? "yes" : "no");
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, upd, nowNode << 1);
    if(uright > mid)update(uleft, uright, upd, nowNode << 1 | 1);
    PushUp(nowNode);
}

double query(int qleft = 1, int qright = rp, int nowNode = 1){
    double ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright){
        return Tree[nowNode].sum;
    }
    PushDown(nowNode);
    int mid = (left + right) >> 1;
    if(qleft <= mid)ret += query(qleft, qright, nowNode<<1);
    if(qright > mid)ret += query(qleft, qright, nowNode<<1|1);
    PushUp(nowNode);
}

void init(){
    p = rp = 1;
    A = 0;
}

bool operator< (Segment a, Segment b){
    return a.h < b.h;
}

int bs(double e, double arr[], int left, int right){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int idx(double x){
    return bs(x, rec, 1, p);
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[p].l = seg[p+1].l = x1;
            seg[p].r = seg[p+1].r = x2;
            seg[p].side = 1;
            seg[p+1].side = -1;
            seg[p++].h = y1, seg[p++].h = y2;
            //printf("rp = %d!\n", rp);
            rec[rp++] = x1, rec[rp++] = x2;
        }
        sort(rec + 1, rec + rp);
        rp = unique(rec + 1, rec + rp) - rec;
        sort(seg + 1, seg + p);
        build();
        /*for(int i = 0; i < rp; ++ i)
            printf("%d:%f\n", i, rec[i]);*/
        double prevh = seg[1].h;
        for(int i = 1; i < p; ++ i){
            int l = idx(seg[i].l), r = idx(seg[i].r);
            printf("updating: %f to %f\n", rec[l], rec[r]);
            update(l, r, seg[i].side > 0);
            A += (seg[i].h - prevh) * query();
            printf("query = %f\n", query());
        }
        printf("%f\n", A);
    }
    return 0;
}