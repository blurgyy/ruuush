#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int T;
int n, k;
int a[maxn];

bool cmp(int a, int b){
    return a > b;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        ll ans = k;
        sort(a, a + n, cmp);
        for(int i = 0; i < n-1; ++ i){
            if(a[i] < k){
                a[i] = k;
            }
            ans += max(a[i], k);
        }
        ans += a[n-1];
        printf("%lld\n", ans);
    }
    return 0;
}
