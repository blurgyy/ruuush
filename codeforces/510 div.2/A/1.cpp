#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n, m;
int a[maxn];

int main(){
    while(~scanf("%d%d", &n, &m)){
        int curmax = -1;
        int ans1, ans2;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            curmax = max(curmax, a[i]);
        }
        ans2 = curmax + m;
        ans1 = curmax;
        for(int i = 1; i <= n; ++ i){
            if(a[i] < curmax){
                if(m >= curmax - a[i]){
                    m -= curmax - a[i];
                    a[i] = curmax;
                }
                else {
                    ans1 = curmax;
                    a[i] += m;
                    m = 0;
                }
            }
        }
        if(m > 0){
            int x = ceil((m * 1.0) / (n * 1.0));
            ans1 = x + curmax;
        }
        printf("%d %d", ans1, ans2);
    }
    return 0;
}