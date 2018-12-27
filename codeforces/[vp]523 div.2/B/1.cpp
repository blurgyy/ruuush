#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n, m;
int a[maxn];
bool vis[maxn];

int main(){
    while(~scanf("%d%d", &n, &m)){
        memset(vis, false, sizeof(vis));
        ll res = 0, sum = 0;
        ll rmv = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            sum += a[i];
        }
        sort(a+1, a+1 + n);
        int lastz = 1;
        for(int i = 1; i < n; ++ i){
            res += 1;
            if(a[i] >= lastz){
                lastz ++;
            }
        }
        res += max(1, a[n] - lastz + 1);
        printf("%I64d\n", sum - res);
    }
    return 0;
}