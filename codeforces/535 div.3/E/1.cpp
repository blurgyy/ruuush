/// not solved
/// (what is this

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 310;
const int inf = 0x3f3f3f3f;

int n, m, p;
int a[maxn];
pii itv[maxn];

struct segTree
{
    int left, right;
    ll sum, lazy, minx;
    void update(ll val){
        sum += (right - left + 1) * val;
        minx += val;
        lazy += val;
    }
}Tree[4*maxn];

void pushDown(int index){
    ll val = Tree[index].lazy;
    if(val){
        Tree[index<<1].update(val);
        Tree[index<<1|1].update(val);
        Tree[index].lazy = 0;
    }
}

void pushUp(int index){
    Tree[index].sum = Tree[index<<1].sum + Tree[index<<1|1].sum;
    Tree[index].minx = min(Tree[index<<1].minx, Tree[index<<1|1].minx);
}

void Build(int nowNode, int left, int right){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].lazy = 0;
    Tree[nowNode].minx = inf;
    if(left == right){
        Tree[nowNode].sum = a[left];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int addVal){
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(uleft <= l && r <= uright){
        Tree[nowNode].update(addVal);
        return;
    }
    pushDown(nowNode);
    int mid = (l + r)>>1;
    if(uleft <= mid)Update(nowNode<<1, uleft, uright, addVal);
    if(uright > mid)Update(nowNode<<1|1, uleft, uright, addVal);
    pushUp(nowNode);
}

ll Query(int nowNode, int qleft, int qright){
    if(qleft > qright) return inf;
    ll ans = 0;
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(qleft <= l && r <= qright)return Tree[nowNode].sum;
    pushDown(nowNode);
    int mid = (l + r)>>1;
    if(qleft <= mid)ans += Query(nowNode<<1, qleft, qright);
    if(qright > mid)ans += Query(nowNode<<1|1, qleft, qright);
    pushUp(nowNode);
    return ans;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        p = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        while(m --){
            int l, r;
            scanf("%d%d", &l, &r);
            itv[p++] = make_pair(l, r);
        }
        int ans = inf;
        for(int i = 1; i <= n; ++ i){
            Build(1, 1, n);
            for(int j = 0; j < p; ++ j){
                int nl = itv[j].first;
                int nr = itv[j].second;
                if(nl <= i && nr >= i) continue;
                Update(1, nl, nr, -1);
            }
            int curans = Query(1, i, i) - min(Query(1, 1, i-1), Query(1, i+1, n));
            ans = min(ans, curans);
        }
        printf("%d\n", ans);
    }
    return 0;
}