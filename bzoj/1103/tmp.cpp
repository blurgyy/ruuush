//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
int n, m, a, b, p, tot;
int pos[maxn], val[maxn], len[maxn], d[maxn];
char op[2];

int dfs(int pre = -1, int idx = 1, int depth = 0){
    //printf("idx = %d, depth = %d\n", idx, depth);
    int ret = E[idx].size() - 1;
    pos[idx] = ++ p;
    val[p-1] = idx;
    d[tot++] = depth;
    //printf("d[%d] = %d\n", idx, d[idx]);
    //printf("size = %d\n", E[4].size());
    for(int i = 0; i < E[idx].size(); ++ i){
        if(E[idx][i] == pre)continue;
        ret += dfs(idx, E[idx][i], depth + 1);
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

void build(int left = 1, int right = n, int nowNode = 1){
    //printf("Tree[%d]: left = %d, right = %d\n", nowNode, left, right);
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].diff = 0;
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    //pushUp(nowNode);
}

void update(int uleft, int uright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("updating: %d %d, current: %d %d\n", uleft, uright, left, right);           ///debugging here
    if(uleft <= left && right <= uright){
        Tree[nowNode].upd(-1);
        //printf("Tree[%d].diff = %d, l = %d, r = %d\n", nowNode, Tree[nowNode].diff, Tree[nowNode].left, Tree[nowNode].right);
        return;
    }
    pushDown(nowNode);
    int mid = (left + right) >> 1;
    if(uleft <= mid)update(uleft, uright, nowNode << 1);
    if(uright > mid)update(uleft, uright, nowNode << 1 | 1);
}

int query(int idx, int nowNode = 1){
    if(Tree[nowNode].left == Tree[nowNode].right)return Tree[nowNode].diff;
    pushDown(nowNode);
    int mid = (Tree[nowNode].left + Tree[nowNode].right) >> 1;
    if(idx <= mid)return query(idx, nowNode << 1);
    return query(idx, nowNode << 1 | 1);
}

void init(){
    //for(int i = 0; i < maxn; ++ i)
        //E[i].clear();
    //memset(vis, false, sizeof(vis));
    p = tot = 0;
}

int main(){
    //freopen("in.in", "r", stdin);

    //while(~scanf("%d", &n))
    {
        scanf("%d", &n);
        init();
        for(int i = 1; i < n; ++ i){
            scanf("%d%d", &a, &b);
            E[a].push_back(b);
            E[b].push_back(a);
        }
        dfs();
/*
        for(int i = 1; i <= n; ++ i){
            printf("d[%d] = %d\n", i, d[i]);
        }
*/
        build();
        scanf("%d", &m);
        m = m + n - 1;
        while(m --){
            scanf("%s", op);
            if(!strcmp(op, "W")){
                scanf("%d", &a);
                //printf("%d\n", query(pos[a]));
                printf("%d\n", d[pos[a]] + query(pos[a]));
            }
            else {
                scanf("%d%d", &a, &b);
                //printf("%d to %d\n", pos[b], pos[b] + len[b]);
                update(pos[max(a, b)], pos[max(a, b)] + len[(max(a, b))]);
            }
        }
    }
    return 0;
}

/**

8
1 2
1 3
1 4
4 5
4 6
6 7
6 8
500

*/