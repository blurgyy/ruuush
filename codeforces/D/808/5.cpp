#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
ll a[maxn], pref[maxn];
map<ll, int> front, rear;

int main(){
    while(~scanf("%d", &n)){
        front.clear();
        rear.clear();
        scanf("%I64d", a);
        pref[0] = a[0];
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", a + i);
            pref[i] = pref[i-1] + a[i];
            rear[a[i]] ++;
        }
        if(pref[n-1] & 1){
            printf("NO\n");
            continue;
        }
        bool ans = false;
        for(int i = 0; i < n; ++ i){
            rear[a[i]] --;
            ll find = (pref[n-1] - pref[i] * 2) >> 1;
            if(find >= 0 && rear[find] > 0){
                ans = true;
                break;
            }
            if(find <= 0 && front[-find] > 0){
                ans = true;
                break;
            }
            front[a[i]] ++;
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}