//#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
const int maxn = 100010;

int fa[maxn];
int u, v, Case = 0;
int rec[maxn], p;
bool ans;

int Find(int x){
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Unite(int x, int y){
    if(Find(x) == Find(y))return;
    fa[Find(x)] = Find(y);
}

bool Same(int x, int y){
    return Find(x) == Find(y);
}

void init(){
    ans = true;
    p = 0;
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d%d", &u, &v) && u >= 0 && v >= 0){
        init();
        rec[p++] = u, rec[p++] = v;
        if(!u && !v){
            printf("Case %d is a tree.\n", ++ Case);
            continue;
        }
        if(u == v)ans = false;
        Unite(u, v);
        while(true){
            scanf("%d%d", &u, &v);
            if(!u && !v)break;
            rec[p++] = u, rec[p++] = v;
            if(Same(u, v))ans = false;
            Unite(u, v);
        }
        for(int i = 0; i < p; ++ i)
            if(!Same(rec[0], rec[i])){
                ans = false;
                break;
            }
        printf("Case %d is ", ++ Case);
        if(ans)printf("a tree.\n");
        else printf("not a tree.\n");
    }
    return 0;
}