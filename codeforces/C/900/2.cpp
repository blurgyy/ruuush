#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

struct SegTreeNode{
    int left, right;
    int sum;
}Tree[maxn<<2];
int n, a[maxn];
int val[maxn];
int ans;

void PushUp(int nowNode){
    Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void build(int left = 1, int right = n, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].sum = 0;
    if(left == right)return;
    int mid((left + right) >> 1);
    build(left, mid, nowNode<<1);
    build(mid + 1, right, nowNode<<1|1);
    //PushUp(nowNode);
    return;
}

void update(int idx, int add = 1, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right){
        Tree[nowNode].sum += add;
        return;
    }
    int mid((left + right) >> 1);
    if(idx <= mid)update(idx, add, nowNode<<1);
    else update(idx, add, nowNode<<1|1);
    PushUp(nowNode);
}

int query(int qleft, int qright, int nowNode = 1){
    if(qleft > qright)return 0;
    int ret = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return Tree[nowNode].sum;
    int mid((left + right) >> 1);
    if(qleft <= mid)ret += query(qleft, qright, nowNode<<1);
    if(qright > mid)ret += query(qleft, qright, nowNode<<1|1);
    return ret;
}

void init(){
    memset(val, 0, sizeof(val));
    ans = INF;
    build();
}

void out(int *begin, int *end){
    for(int *i = begin; i < end; ++ i)
        printf("%d%c", *i, " \n"[i == end-1]);
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        init();
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            val[a[i]] = (query(a[i]+1, n) == 0) * query(1, a[i]-1);
            if(val[a[i]] == 0)ans = min(ans, a[i]);
            //printf("(%d to %d)%d, (%d to %d)%d\n", a[i]+1, n, query(a[i]+1, n), 1, a[i]-1, query(1, a[i]-1));
            update(a[i]);
        }
        for(int i = 1; i <= n; ++ i)
            printf("%d%c", val[a[i]], " \n"[i == n]);
        printf("%d\n", ans);
    }
    return 0;
}

/**

6
6 5 4 3 2 1

*/