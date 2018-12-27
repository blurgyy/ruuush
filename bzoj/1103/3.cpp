//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 250010;

struct SegTree{
    int left, right;
    int diff;
    void upd(int val = -1){
        diff += val;
    }
}Tree[maxn<<2];
vector<int> E[maxn];
int n, m, a, b, p = 0;
int pos[maxn], len[maxn], val[maxn], d[maxn];
bool vis[maxn];
char op[2];

int dfs(int idx = 1, int depth = 0){
    vis[idx] = true;
    pos[idx] = ++ p;
    val[p-1] = idx;
    d[idx] = depth;
    int ret = E[idx].size() - 1;
    for(int i = 0; i < E[idx].size(); ++ i){
        if(vis[E[idx][i]])continue;
        ret += dfs(E[idx][i], depth + 1);
    }
    len[idx] = ret;
    return ret;
}

void pushDown(int nowNode){
    int val = Tree[nowNode].diff;
    if(val){
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].diff = 0;
    }
}

void build(int left = 1, int right = p, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].diff = 0;
    if(left == right)return;
    int mid((left + right) >> 1);
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
}

void update(int uleft, int uright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].upd();
        return;
    }
    pushDown(nowNode);
    int mid((left + right) >> 1);
    if(uleft <= mid)update(uleft, uright, nowNode << 1);
    if(uright > mid)update(uleft, uright, nowNode << 1 | 1);
}

int query(int pos, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right)return Tree[nowNode].diff;
    pushDown(nowNode);
    int mid((left + right) >> 1);
    if(pos <= mid)return query(pos, nowNode << 1);
    return query(pos, nowNode << 1 | 1);
}

int main() {
    //freopen("in.in", "r", stdin);
    scanf("%d", &n);
    for(int i = 1; i < n; ++ i) {
        scanf("%d%d", &a, &b);
        E[a].push_back(b);
        E[b].push_back(a);
    }
    dfs();
    build();
    scanf("%d", &m);
    m = m + n - 1;
    while(m --){
        scanf("%s", op);
        if(!strcmp(op, "A")){
            scanf("%d%d", &a, &b);
            a = max(a, b);
            update(pos[a], pos[a] + len[a]);
        }
        else {
            scanf("%d", &a);
            printf("%d\n", d[a] + query(pos[a]));
        }
    }
    return 0;
}