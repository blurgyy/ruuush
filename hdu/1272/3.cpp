#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int fa[maxn], u, v, p;
bool ans = true;

void init(){
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
    p = 0;
    ans = true;
}

int main(){
    while(~scanf("%d%d", &u, &v)){
        if(u == -1 && v == -1)
            break;
        init();
        if()
    }
}