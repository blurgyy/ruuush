#include <bits/stdc++.h>
using namespace std;
const size_t maxn = 100010;

int n, m, k;
int pos[maxn];
int d[maxn];

int main(){
    while(~scanf("%d%d%d", &n, &m, &k)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", pos + i);
        }
        for(int i = 1; i < n; ++ i){
            d[i] = pos[i] - pos[i-1] - 1;
        }
        sort(d+1, d+n);
        int ans = n;
        for(int i = n-k; i; -- i){
            ans += d[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}