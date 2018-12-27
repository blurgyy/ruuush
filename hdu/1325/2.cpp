//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>

using namespace std;
const int maxn = 10010;
const char out[2][50] = {"not a tree", "a tree"};

int fa[maxn];
int u, v, Case = 0;
int rec[maxn], p;

int Find(int x){
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Unite(int x, int y){
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool Same(int x, int y){
    return Find(x) == Find(y);
}

void init(){
    p = 0;
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d%d", &u, &v) && u >= 0 && v >= 0){
        init();
        Unite(u, v);
        bool ans = true;
        if(u == v)ans = false;
        rec[p++] = u;
        rec[p++] = v;
        int anc = u;
        while(true){
            scanf("%d%d", &u, &v);
            if(!u && !v)break;
            rec[p++] = u;
            rec[p++] = v;
            if(Same(u, v))ans = false;
            Unite(u, v);
        }
        for(int i = 0; i < p; ++ i)
            if(Find(anc) != Find(rec[i])){
                ans = false;
                break;
            }
        printf("Case %d is %s.\n", ++ Case, out[ans]);
    }
    return 0;
}