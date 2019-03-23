#include <bits/stdc++.h>
using namespace std;

int n, m;

int main(){
    while(~scanf("%d%d", &n, &m)){
        int x = m / n;
        if(n * x != m){
            printf("-1\n");
            continue;
        }
        int ans = 0;
        while(x > 1){
            if(x % 2 == 0){
                x /= 2;
            }
            else {
                if(x % 3 == 0){
                    x /= 3;
                }
                else {
                    break;
                }
            }
            ans ++;
        }
        if(x != 1) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
