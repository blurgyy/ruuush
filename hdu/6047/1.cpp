#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 250010;
const ll mod = 1e9 + 7;

int n;
ll ans;
ll a[maxn], b[maxn];

void init(){
    ans = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        priority_queue<pair<ll, int> > que;
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", a + i);
            que.push(make_pair(a[i] - i, -i));
        }
        for(int i = 1; i <= n; ++ i)
            scanf("%lld", b + i);
        sort(b + 1, b + n + 1);
        for(int i = 1; i <= n; ++ i){
            /*int pos = -que.top().second;
            //printf("b[%d] = %lld, pos = %d, ", i, b[i], pos);
            while(pos < b[i]){
                que.pop();
                pos = -que.top().second;
            }*/
            //printf("pos = %d, ", pos);
            while(-que.top().second < b[i])
                que.pop();
            int now = que.top().first;
            que.push(make_pair(now - n - 1, -n-1));
            ans = (ans + now) % mod;
            //printf("ans = %d\n", ans);
        }
        printf("%lld\n", ans);
    }
    return 0;
}