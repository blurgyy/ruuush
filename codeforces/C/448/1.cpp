#include<bits/stdc++.h>
using namespace std;
const int maxn = 5010;
const int INF = 0x3f3f3f3f;

struct SegTree
{
    int left, right;
    int lazy, max, min;
    void update(int val){
        max += val;
        min += val;
        lazy += val;
    }
}Tree[maxn<<2];
int n, a[maxn], ans;

void PushDown(int nowNode){
    int val = Tree[nowNode].lazy;
    if(val){
        Tree[nowNode].lazy = 0;
        Tree[nowNode].update(val);
        Tree[nowNode].update(val);
    }
}

void PushUp(int nowNode){
    Tree[nowNode].max = max(Tree[nowNode<<1].max, Tree[nowNode<<1|1].max);
    Tree[nowNode].min = min(Tree[nowNode<<1].min, Tree[nowNode<<1|1].min);
}

void Build(int left = 1, int right = n, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].lazy = 0;
    if(left == right){
        Tree[nowNode].max = Tree[nowNode].min = a[right];
        return;
    }
    int mid = (left + right) >> 1;
    Build(left, mid, nowNode<<1);
    Build(mid+1, right, nowNode<<1|1);
    PushUp(nowNode);
}

void Update(int uleft, int uright, int addVal, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].update(addVal);
        return;
    }
    int mid = (left + right) >> 1;
    PushDown(nowNode);
    if(uleft <= mid)Update(uleft, uright, addVal, nowNode<<1);
    if(uright > mid)Update(uleft, uright, addVal, nowNode<<1|1);
    PushUp(nowNode);
}

pair<int, int> Query(int qleft, int qright, int nowNode = 1){///<max, min>
    int a = -1, b = INF;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)
        return make_pair(Tree[nowNode].max, Tree[nowNode].min);
    int mid = (left + right) >> 1;
    PushDown(nowNode);
    if(qleft <= mid){
        a = max(a, (Query(qleft, qright, nowNode<<1)).first);
    }
    if(qright < mid){
        b = min(b, (Query(qleft, qright, nowNode<<1|1)).second);
    }
    PushUp(nowNode);
    return make_pair(a, b);
}

void solve(int l, int r){//begin(), end()
    pair<int, int> cur = Query(l, r);
    int mx = cur.first, mn = cur.second;
    if(mx <= r-l)///////////////////////////////////////////////////改天再写我要睡觉i_i
    for(int i = l; i < r; ++ i)
        a[i] -= mn;
    Update(l, r-1, -mn);
    int nxtl = 0, nxtr = INF;
    for(int i = l; i < r; ++ i){
        a[i] -= i;
        if(a[i] == 0){
            if(nxtl < i+1)nxtl = i+1;
            if(nxtr > i)nxtr = i;
        }
    }
}

int main(){
    while(~scanf("%d", &n)){
        ans = 0;
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        Build();
        solve(1, n+1);
    }
    //exit(0);
    return 0;
}