#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k;
int a[maxn];

int main(){
    while(~scanf("%d%d", &n, &k)){
        int ma = -INF, mn = INF;
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            ma = max(a[i], ma);
            mn = min(a[i], mn);
        }
        if(n == k){
            printf("%d\n", ma);
            continue;
        }
        if(k == 1){
            printf("%d\n", mn);
            continue;
        }
        if(k > 2){
            printf("%d\n", ma);
            continue;
        }
        int t1 = INF, t2 = INF;
        int tt = -INF;
        for(int i = 0; i < n; ++ i){
            t1 = min(t1, a[i]);
            tt = max(t1, tt);
        }
        for(int i = n-1; i >= 0; -- i){
            t2 = min(t2, a[i]);
            tt = max(t2, tt);
        }
        printf("%d\n", tt);
    }
    return 0;
}