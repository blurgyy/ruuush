#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k;
int a[maxn];

int main(){
    //printf("%d\n", INF);
    while(~scanf("%d%d", &n, &k)){
        int ans = -INF;
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        if(k > 1){
            for(int i = 0; i < n; ++ i)
                ans = max(ans, a[i]);
            printf("%d\n", ans);
            continue;
        }
        ans = INF;
        for(int i = 0; i < n; ++ i)
            ans = min(ans, a[i]);
        printf("%d\n", ans);
    }
    return 0;
}