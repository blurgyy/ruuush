//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 500010;
char out[2][10] = {"No", "Yes"};

int fa[maxn], u, v, p, rec[maxn];
bool ans;

int find(int x){
    return x == fa[x] ? x : find(fa[x]);
}

bool same(int x, int y){
    return find(x) == find(y);
}

void unite(int x, int y){
    if(same(x, y))return;
    fa[find(x)] = find(y);
}

void init(){
    ans = true;
    p = 0;
}

void record(){
    rec[p++] = u, rec[p++] = v;
}

int main(){
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
    while(~scanf("%d%d", &u, &v)){
        if(!u && !v){
            printf("Yes\n");
            continue;
        }
        if(u == -1 && v == -1){
            break;
        }
        init();
        unite(u, v);
        record();
        while(true){
            scanf("%d%d", &u, &v);
            if(!u && !v)break;
            record();
            if(same(u, v)){
                //printf("u = %d, v = %d\n", u, v);
                ans = false;
                continue;
            }
            unite(u, v);
        }
        for(int i = 1; i < p; ++ i)
            if(!same(rec[i-1], rec[i])){
                ans = false;
                break;
            }
        printf("%s\n", out[ans]);
        for(int i = 0; i < p; ++ i){
            fa[rec[i]] = rec[i];
        }
    }
    return 0;
}