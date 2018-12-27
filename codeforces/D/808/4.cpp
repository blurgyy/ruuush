#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
ll a[maxn], pref[maxn];
map<ll, int> rec;

int main(){
    while(~scanf("%d", &n)){
        rec.clear();
        scanf("%I64d", a);
        pref[0] = a[0];
        rec[a[0]] ++;
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", a + i);
            rec[a[i]] ++;
            pref[i] = pref[i-1] + a[i];
        }
        if(pref[n-1] & 1){
            printf("NO\n");
            continue;
        }
        bool ans = false;
        ll sum = pref[n-1];
        for(int i = 0; i < n; ++ i){
            rec[a[i]] --;
            ll find = (sum - pref[i]*2) >> 1;
            if(find < 0)break;
            if(rec[find] > 0){
                ans = true;
                break;
            }
        }
        rec.clear();
        for(int i = 0; i < n; ++ i)
            rec[a[i]] ++;
        for(int i = n-1; i > 0; -- i){
            rec[a[i]] --;
            ll find = (pref[i] * 2 - sum) >> 1;
            if(find < 0)break;
            if(rec[find] > 0){
                ans = true;
                break;
            }
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}