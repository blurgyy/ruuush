//wtf tle

#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const char out[2][50] = {"not a tree", "a tree"};

int u, v, Case = 0;
struct Ufind{
    int fa[maxn];

    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y){
        int t1 = find(x);
        int t2 = find(y);
        if(t1 == t2)return;
        fa[t1] = t2;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    void init(int n = maxn){
        for(int i = 0; i < n; ++ i)
            fa[i] = i;
    }
}uf;

int main(){
    while(~scanf("%d%d", &u, &v) && u != -1 && v != -1){
        bool ans = true;
        uf.init();
        uf.unite(u, v);
        while(true){
            scanf("%d%d", &u, &v);
            if(u == 0 && v == 0)break;
            if(uf.same(u, v))
                ans = false;
            uf.unite(u, v);
        }
        printf("Case %d is %s.\n", ++ Case, out[ans]);
    }
    return 0;
}