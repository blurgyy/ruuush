#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;
const int maxn = 100010;

int n, top;
ll a[maxn], pref[maxn], stk[maxn];
pair<ll, ll> itv[maxn];

void init(){
    top = 0;
    pref[0] = 0;
    for(int i = 0; i <= n; ++ i){
        itv[i].first = 0;
        itv[i].second = n+1;
    }
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &n);{
    //while(~scanf("%d", &n)){
        init();
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", a + i);
            pref[i] = pref[i-1] + a[i];
            while(top && a[i] < a[stk[top-1]])
                itv[stk[--top]].second = i;
            stk[top++] = i;
        }
        top = 0;
        for(int i = n; i > 0; -- i){
            while(top && a[i] < a[stk[top-1]])
                itv[stk[--top]].first = i;
            stk[top++] = i;
        }
        ll ans = -1;
        int pos;
        for(int i = 1; i <= n; ++ i){
            ll now = a[i] * (pref[itv[i].second-1] - pref[itv[i].first]);
            if(now > ans){
                ans = now;
                pos = i;
            }
        }
        printf("%lld\n%lld %lld\n", ans, itv[pos].first+1, itv[pos].second-1);
    }
    return 0;
}