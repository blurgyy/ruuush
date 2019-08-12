#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 200010;

int T, n;
ll h[maxn];
bool inq[maxn];
priority_queue<pii> que;

void init(){
    while(que.size()) que.pop();
    memset(h, -1, sizeof(h));
    memset(inq, false, sizeof(inq));
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        ll sum = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", h + i);
            sum += h[i];
        }
        for(int i = n; i; -- i){
            if(h[i*2] == -1 && h[i*2+1] == -1){
                que.push(make_pair(h[i], i));
                inq[i] = true;
            }
            else {
                break;
            }
        }
        // printf("que.size() = %d\n", que.size());
        ll ans = 0;
        while(!que.empty()){
            // printf("size = %d\n", que.size());
            pii now = que.top();
            que.pop();
            ans += now.first;
            if(now.second > 1 && !inq[now.second/2]){
                que.push(make_pair(h[now.second/2], now.second/2));
                inq[now.second/2] = true;
            }
            if(que.empty()){
                break;
            }
            now = que.top();
            que.pop();
            if(now.second > 1 && !inq[now.second/2]){
                que.push(make_pair(h[now.second/2], now.second/2));
                inq[now.second/2] = true;
            }
        }
        printf("%lld %lld\n", ans, sum - ans);
    }
    return 0;
}
