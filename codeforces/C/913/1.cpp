#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 50;

struct node{
    int val;
    ll price, after;
}a[maxn];
int n;
ll l;

bool operator< (node a, node b){
    if(a.after == b.after)
        return a.val > b.val;
    return a.after < b.after;
}

int main(){
    while(~scanf("%d%I64d", &n, &l)){
        memset(a, 0, sizeof(a));
        for(int i = 0; i < maxn; ++ i)
            a[i].val = 1<<(i);
        for(int i = 0; i < n; ++ i){
            scanf("%I64d", &a[i].price);
            a[i].after = a[i].price<<(n-i);
        }
        for(int i = 0; i < n; ++ i)
            printf("%d, %lld, %lld\n", a[i].val, a[i].price, a[i].after);
        sort(a, a + n);
        ll ans = 0;
        for(int i = 0; i < n; ++ i){
            if(l == 0)break;
            if(a[i].val >= l){
                ans += a[i].price;
                break;
            }
            else {
                ans += l / a[i].val * a[i].price;
                l %= a[i].val;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}