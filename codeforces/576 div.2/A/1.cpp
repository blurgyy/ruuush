#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int n, x, y;
int a[maxn];

int miniv(int l, int r){
    l = max(l, 1);
    r = min(r, n);
    int ret = inf;
    if(l > r){
        return ret;
    }
    for(int i = l; i <= r; ++ i){
        ret = min(ret, a[i]);
    }
    return ret;
}

int main(){
    while(~scanf("%d%d%d", &n, &x, &y)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        int ans = -1;
        for(int i = 1; i <= n; ++ i){
            if(miniv(i-x, i-1) <= a[i]) continue;
            if(miniv(i+1, i+y) <= a[i]) continue;
            ans = i;
            break;
        }
        printf("%d\n", ans);
    }
    return 0;
}
