#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Segment{
    double l, r, h;
    int side;   //-1 for top, 1 for bottom
}segment[maxn];
struct SegTree{
    int left, right;
    bool inp;
    double sum;
    //int side;   //-1 for top, 1 for bottom
}Tree[maxn<<2];
int n, p, rp, Case = 0;
double x1, y1, x2, y2, rec[maxn], A;

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void PushDown(int nowNode){
    if(Tree[nowNode].inp){
        Tree[nowNode<<1].sum = rec[Tree[nowNode<<1].right] - rec[Tree[nowNode<<1].left];
        Tree[nowNode<<1|1].sum = rec[Tree[nowNode<<1|1].right] - rec[Tree[nowNode<<1|1].left];
        Tree[nowNode<<1].inp = !(Tree[nowNode<<1].left == Tree[nowNode<<1].right);
        Tree[nowNode<<1|1].inp = !(Tree[nowNode<<1|1].left == Tree[nowNode<<1|1].right);
    }
}

void build(int left = 1, int right = p, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left >= right){
        Tree[nowNode].sum = 0;
        Tree[nowNode].inp = false;
        return;
    }
    int mid((left + right) >> 1);
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    PushUp(nowNode);
}

void update(int uleft, int uright, int addval, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].sum += addval * (rec[right] - rec[left]);
        Tree[nowNode].inp = true;
        return;
    }
    PushDown(nowNode);
    int mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, addval, nowNode << 1);
    if(uright > mid)update(uleft, uright, addval, nowNode << 1 | 1);
    PushUp(nowNode);
}

double query(int qleft = 1, int qright = p, int nowNode = 1){
    double ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright){
        return Tree[nowNode].sum;
    }
    PushDown(nowNode);
    int mid((left + right) >> 1);
    if(qleft <= mid)ret += query(qleft, qright, nowNode<<1);
    if(qright > mid)ret += query(qleft, qright, nowNode<<1|1);
    PushUp(nowNode);
    return ret;
}

void init(){
    p = rp = 1;
    A = 0;
    memset(Tree, 0, sizeof(Tree));
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

bool operator< (Segment a, Segment b){
    return a.h < b.h;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n) && n){
        init();
        for(int i = 0; i < n; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            segment[p].l = x1, segment[p].r = x2, segment[p].side = -1, segment[p++].h = y1;
            segment[p].l = x1, segment[p].r = x2, segment[p].side =  1, segment[p++].h = y2;
            rec[rp++] = x1, rec[rp++] = x2;
        }
        sort(segment + 1, segment + p);
        sort(rec + 1, rec + rp);
        build();
        double prevh = segment[1].h;
        for(int i = 1; i < p; ++ i){
            int left = idx(segment[i].l), right = idx(segment[i].r);
            update(left, right, segment[i].side);
            printf("add_h = %f\tlength = %f\n", segment[i].h - prevh, rec[right] - rec[left]);
            A += (segment[i].h - prevh) * query();
            prevh = segment[i].h;
            printf("A = %f\n", A);
        }
        printf("%f\n", A);
    }
    return 0;
}