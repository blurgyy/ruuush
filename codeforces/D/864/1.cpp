//Unsolved

#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

struct node
{
    int v, pos;
    bool operator< (node b){
        return v < b.v;
    }
}a[maxn];
int n;
set<int> all;

bool cmp(node a, node b){
    return a.pos < b.pos;
}

int Find(){
    for(int i = 0; i < n; ++ i)
        if(!a[i].v)return i;
}

int main(){
    while(~scanf("%d", &n)){
        all.clear();
        for(int i = 0; i < n; ++ i){
            scanf("%d", &a[i].v);
            all.insert(a[i].v);
            a[i].pos = i;
        }
        sort(a, a + n);
        int cnt = 0;
        for(int i = 1; i < n; ++ i){
            if(a[i].v == a[i-1].v){
                a[i-1].v = 0;
                ++ cnt;
            }
        }
        sort(a, a + cnt, cmp);
        int p = 0;
        for(int i = 1; i <= n; ++ i){
            if(all.find(i) != all.end())continue;
            a[p++].v = i;
        }
        sort(a, a + n, cmp);
        printf("%d\n", cnt);
        printf("%d", a[0].v);
        for(int i = 1; i < n; ++ i)
            printf(" %d", a[i].v);
        printf("\n");
    }
    return 0;
}