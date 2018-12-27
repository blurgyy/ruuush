//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
//using namespace std;
typedef long long ll;
const int maxn = 100010;

struct SegTree{
    int left, right;
    ll val, lazy;
    void upd(ll n){
        val += (right - left + 1) * n;
        lazy += n;
    }
}Tree[maxn<<2];
int N, Q;
ll A[maxn];

void PushUp(int nowNode){
    Tree[nowNode].val = Tree[nowNode<<1].val + Tree[nowNode<<1|1].val;
}

void PushDown(int nowNode){
    ll n = Tree[nowNode].lazy;
    if(n){
        Tree[nowNode<<1].upd(n);
        Tree[nowNode<<1|1].upd(n);
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = N, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].val = A[right];
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    PushUp(nowNode);
    //printf("%d, (%d, %d) Tree[%d].val = %lld\n", nowNode, left, right, nowNode, Tree[nowNode].val);
}

void update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].upd(addVal);
        return;
    }
    int mid = (left + right) >> 1;
    PushDown(nowNode);
    if(uleft <= mid)update(uleft, uright, addVal, nowNode << 1);
    if(uright > mid)update(uleft, uright, addVal, nowNode << 1 | 1);
    PushUp(nowNode);
}

ll query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright){
        //printf("Tree[%d].val = %lld\n", nowNode, Tree[nowNode].val);
        return Tree[nowNode].val;
    }
    ll ret = 0;
    PushDown(nowNode);
    int mid = (left + right) >> 1;

    if(qleft <= mid){
        //printf("l: %lld\n", query(qleft, qright, nowNode << 1));
        ret += query(qleft, qright, nowNode << 1);
    }
    if(qright > mid){
        //printf("r: %lld\n", query(qleft, qright, nowNode << 1 | 1));
        ret += query(qleft, qright, nowNode << 1 | 1);
    }
    PushUp(nowNode);
    return ret;
}

int main(){
    while(~scanf("%d%d", &N, &Q)){
        for(int i = 1; i <= N; ++ i)
            scanf("%lld", A + i);
        build();
        char op[2];
        int a, b, c;
        while(Q--){
            scanf("%s", op);
            if(!strcmp(op, "Q")){
                scanf("%d%d", &a, &b);
                printf("%lld\n", query(a, b));
            }
            else{
                scanf("%d%d%d", &a, &b, &c);
                update(a, b, c);
            }
        }
    }
    return 0;
}