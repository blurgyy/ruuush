/// :)

//#include<bits/stdc++.h>
//using namespace std;
#include<cstdio>
#include<cstring>
typedef long long ll;
const int maxn = 1000010;

struct SegTree{
    int left, right;
    ll sum, lazy;
    void upd(ll val){
        sum += (right - left + 1) * val;
        lazy += val;
    }
}Tree[maxn<<2];
int n, q;
ll a[maxn];
char op[2];

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void PushDown(int nowNode){
    ll val = Tree[nowNode].lazy;
    if(val){
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].lazy = 0;
    }
}

void build(int left = 1, int right = n, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].sum = a[right];
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    PushUp(nowNode);
}

ll query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return Tree[nowNode].sum;
    ll ret = 0;
    int mid = (left + right) >> 1;
    PushDown(nowNode);
    if(qleft <= mid)ret += query(qleft, qright, nowNode << 1);
    if(qright > mid)ret += query(qleft, qright, nowNode << 1 | 1);
    PushUp(nowNode);
    return ret;
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

int main(){
    while(~scanf("%d%d", &n, &q)){
        for(int i = 1; i <= n; ++ i)
            scanf("%lld", a + i);
        build();
        int a, b, c;
        while(q--){
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