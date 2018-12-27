#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

ll n, m, a, d;
ll t[maxn];
int tot;

int bs(ll arr[], ll e, int left = 0, int right = tot - 1){
    if(left >= right)return right;
    int mid = left + (right - left) / 2;
    if(e <= arr[mid])return bs(arr, e, left, mid);
    return bs(arr, e, mid + 1, right);
}

//ll find(ll k, ll left = 1, ll right = n){
//    if(left >= right)return right;
//    ll mid = (left + right) / 2;
//    if(k <= mid * a)return find(k, left, mid);
//    return find(k, mid + 1, right);
//}

int main(){
    while(~scanf("%I64d%I64d%I64d%I64d", &n, &m, &a, &d)){
        tot = 0;
        for(int i = 0, x; i < m; ++ i){
            scanf("%I64d", &x);
            if(i && x == t[i-1])continue;
            t[tot++] = x;
        }
        int now = min(a, t[0]);
        ans ++;
        for(int i = 0; i < tot; ++ i){
            
        }
        printf("%\n");
    }
    return 0;
}