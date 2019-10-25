#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

int n, a[maxn];
ll pref[maxn];

int main(){
    while(~scanf("%d", &n)){
        pref[0] = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            pref[i] = pref[i-1] + a[i];
        }
        int ans = -1;
        for(int i = 1; i <= n; ++ i)
            if(pref[i] >= pref[n] >> 1){
                ans = i;
                break;
            }
        printf("%d\n", ans);
    }
    return 0;
}