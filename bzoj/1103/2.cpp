#include<bits/stdc++.h>
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
int n, m, a, b, p = 1;
int pos[maxn], len[maxn], val[maxn], d[maxn];
bool vis[maxn] = {false};
char op[2];

int dfs(int node = 1, int depth = 0){
    vis[node] = true;
    d[node] = depth;
    pos[node] = p ++;
    val[p-1] = node;
    int ret = E[node].size() - 1;
    for(int i = 0; i < E[node].size(); ++ i){
        if(vis[E[node][i]])continue;
        ret += dfs(E[node][i], depth + 1);
    }
    len[node] = ret;
    return ret;
}

void pushDown(int nowNode){
    int val = Tree[nowNode].diff;
    if(val) {
        Tree[nowNode<<1].upd(val);
        Tree[nowNode<<1|1].upd(val);
        Tree[nowNode].diff = 0;
    }
}

void build(int left = 1, int right = p-1, int nowNode = 1) {
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].diff = 0;
    if(left == right)return;
    int mid = (left + right) >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
}

void update(int uleft, int uright, int nowNode = 1) {
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright){
        Tree[nowNode].upd();
        return;
    }
    pushDown(nowNode);
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, nowNode << 1);
    if(uright > mid)update(uleft, uright, nowNode << 1 | 1);
}

int query(int node, int nowNode = 1) {
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right) return d[node] + Tree[nowNode].diff;
    pushDown(nowNode);
    int mid = (left + right) >> 1;
    if(pos[node] <= mid)return query(node, nowNode << 1);
    return query(node, nowNode << 1 | 1);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; ++ i) {
        scanf("%d%d", &a, &b);
        E[a].push_back(b);
        E[b].push_back(a);
    }
    dfs();
    build();
    scanf("%d", &m);
    m = n + m - 1;
/*
    for(int i = 0; i < n; ++ i) {
        printf("d[%d] = %d\n", i, d[i]);
    }
*/
    for(int i = 0; i < m; ++ i) {
        scanf("%s", op);
        if(!strcmp(op, "A")) {
            scanf("%d%d", &a, &b);
            update(pos[max(a, b)], pos[max(a, b)] + len[max(a, b)]);
        }
        else {
            scanf("%d", &a);
            printf("%d\n", query(a));
        }
    }
    return 0;
}