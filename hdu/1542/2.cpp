#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Segment{
    double l, r, h;
    int side;
}seg[maxn];
struct SegTree{
    int left, right;
    bool inp;
    double sum;
    void upd(int idf){
        sum += (rec[right] - rec[left]) * idf;
        inp = !(left == right);
    }
}Tree[maxn<<2];
int n, p, rp;
double x1, x2, y1, y2, rec[maxn];

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void PushDown(int nowNode, int idf){
    if(Tree[nowNode].inp){
        Tree[nowNode<<1].upd(idf);
        Tree[nowNode<<1|1].upd(idf);
        Tree[nowNode].inp = false;
    }
}

void build(int left = 1, int right = rp, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left >= right){
        Tree[nowNode].inp = false;
        Tree[nownode].sum = 0;
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    PushUp(nowNode);
}

void update(int uleft, int uright, int idf, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].sum += idf * (rec[Tree[nowNode].right] - rec[Tree[nowNode].left]);
        Tree[nowNode].inp = true;
        return;
    }
    PushDown(nowNode, idf);
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, idf, nowNode<<1);
    if(uright > mid)update(uleft, uright, idf, nowNode<<1|1);
    PushUp(nowNode);
}

double query(int qleft, int qright, int nowNode = 1){
    double ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright){
        return Tree[nowNode].sum;
    }
    
}

void init(){
    p = rp = 1;
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
    return bs(x, rec, 1, rp-1);
}

int main(){
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[p].l = x1, seg[p].r = x2, seg[p++].h = y1;
            seg[p].l = x1, seg[p].r = x2, seg[p++].h = y2;
            rec[p++] = x1, rec[p++] = x2;
        }
        sort(rec + 1, rec + rp);
        sort(seg + 1, seg + p);
        double prevh = seg[1].h;
        for(int i = 1; i < p; ++ i){
            int l = idx(seg[i].l), r = idx(seg[i].r);
            update(l, r, seg[i].side);
            A += (seg[i].h - prevh) * query();
        }
        printf("%f\n", A);
    }
    return 0;
}