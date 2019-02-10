#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, s;
int deg[maxn];

int main(){
    while(~scanf("%d%d", &n, &s)){
        memset(deg, 0, sizeof(deg));
        for(int i = 1, u, v; i < n; ++ i){
            scanf("%d%d", &u, &v);
            deg[u] ++;
            deg[v] ++;
        }
        int bot = 0;
        for(int i = 0; i < maxn; ++ i){
            if(deg[i] == 1) bot ++;
        }
        printf("%.10f\n", 2.0 * s / bot);
    }
    return 0;
}