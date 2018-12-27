//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 100010;

int fa[maxn];
int u, v, Case = 0;
int rec[maxn], p;
bool ans;
struct Node
{
    int in, out;
}node[maxn];

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
    p = 0;
    ans = true;
    memset(node, 0, sizeof(node));
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d%d", &u, &v) && u >= 0 && v >= 0){
        if(u == 0 && v == 0){
            printf("Case %d is a tree.\n", ++ Case);
            continue;
        }
        init();
        if(Same(u, v)){
            ans = false;
        }
        Unite(u, v);
        rec[p++] = u, rec[p++] = v;
        while(true){
            scanf("%d%d", &u, &v);
            if(u == 0 && v == 0)break;
            if(Same(u, v)){
                ans = false;
            }
            node[u].out ++;
            node[v].in ++;
            rec[p++] = u, rec[p++] = v;
            Unite(u, v);
        }
        for(int i = 0; i < p; ++ i)
            if(!Same(rec[0], rec[i]) || node[i].in > 1){
                ans = false;
                break;
            }
        if(ans)printf("Case %d is a tree.\n", ++ Case);
        else printf("Case %d is not a tree.\n", ++ Case);
    }
    return 0;
}