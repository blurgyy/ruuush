#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
ll a[maxn], b[maxn], pref[maxn];

int bs(ll e, ll arr[], int left = 0, int right = n-1){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int main(){
    while(~scanf("%d", &n)){
        scanf("%I64d", a);
        pref[0] = b[0] = a[0];
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", a + i);
            b[i] = a[i];
            pref[i] = pref[i-1] + a[i];
        }
        if(pref[n-1] & 1){
            printf("NO\n");
            continue;
        }
        sort(b, b + n);
        if(b[bs(pref[n-1]>>1, b)] == (pref[n-1]>>1)){
            printf("YES\n");
            continue;
        }
        bool ans = false;
        for(int i = 1; i < n; ++ i){
            ll find = (pref[n-1]>>1) - pref[i-1];
            if(b[bs(find, b)] == find){
                printf("%lld, b[%d] = %I64d\n", a[i], bs(find, b), find);
                ans = true;
                break;
            }
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}