#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n;
double a[maxn];
struct SegTreeNode{
    int left, right;
    int lazy;
    double sum;
    void upd(int val){
        sum += (right - left + 1) * val;
        lazy = val;
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

void build(int left = 1, int right = n, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].lazy = 0;
        Tree[nowNode].sum = a[right];
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        Tree[nowNode].upd(addVal);
        return;
    }
    PushDown(nowNode);
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, addVal, nowNode<<1);
    if(uright > mid)update(uleft, uright, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

int main(){
    freopen("int.in", "r", stdin);
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i)
            scanf("%lf", a + i);
        build();
        int q, l, r, val;
        printf("out: %f\n", Tree[1].sum);
        scanf("%d", &q);
        while(q--){
            scanf("%d%d%d", &l, &r, &val);
            update(l, r, val);
            printf("%f\n", Tree[1].sum);
        }
    }
    return 0;
}