#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, a[maxn];
int fa[maxn];
int cir[maxn], root[maxn], pc, pr;

int Find(int x){
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

bool Same(int x, int y){
    return Find(x) == Find(y);
}

void Unite(int x, int y){
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

void init(){
    for(int i = 0; i <= n; ++ i)
        fa[i] = i;
    pc = pr = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            if(i == a[i])
                root[pr++] = i;
            else if(Same(a[i], i))
                cir[pc++] = i;
            Unite(a[i], i);
        }
/*
        for(int i = 0; i < pc; ++ i)
            printf("%d ", cir[i]);
        printf("\n");
        for(int i = 0; i < pr; ++ i)
            printf("%d ", root[i]);
        printf("\n");
*/
        int ans;
        if(pr > 0){
            ans = pc + pr - 1;
            for(int i = 1; i < pr; ++ i)
                a[root[i]] = a[root[0]];
            for(int i = 0; i < pc; ++ i)
                a[cir[i]] = a[root[0]];
        }
        else{
            ans = pc;
            a[cir[0]] = cir[0];
            root[pr++] = cir[0];
            for(int i = 1; i < pc; ++ i)
                a[cir[i]] = root[0];
        }
        printf("%d\n%d", ans, a[1]);
        for(int i = 2; i <= n; ++ i)
            printf(" %d", a[i]);
        printf("\n");
    }
    return 0;
} 