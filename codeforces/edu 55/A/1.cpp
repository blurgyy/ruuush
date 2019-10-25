#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int T;
int n, x, y, d;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d%d", &n, &x, &y, &d);
        int to_last = (n - x) / d;
        if((n - x) % d) to_last ++;

        int to_first = (x - 1) / d;
        if((x - 1) % d) to_first ++;

        int from_last = (n - y) / d;
        if((n - y) % d) from_last ++;

        int from_first = (y - 1) / d;
        if((y - 1) % d) from_first ++;

        int direct = abs(y - x) / d;
        if(abs(y - x) % d) direct ++;

        int ans = inf;
        if((n - y) % d == 0){
            ans = min(ans, to_last + from_last);
        }
        if((y - 1) % d == 0){
            ans = min(ans, to_first + from_first);
        }
        if(abs(y - x) % d == 0){
            ans = min(ans, direct);
        }
        if(ans == inf) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}