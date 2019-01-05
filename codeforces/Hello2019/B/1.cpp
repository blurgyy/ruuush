#include <bits/stdc++.h>
using namespace std;
const int maxn = 16;

int n;
int a[maxn];

bool check(int x){                      /// 1 for '+', 0 for '-';
    int deg = 360 * 100;
    for(int i = 0; i < n; ++ i){
        // printf("%d", (x>>i) & 1);
        if((x >> i) & 1){
            deg += a[i];
        }
        else {
            deg -= a[i];
        }
    }
    return deg % 360 == 0;
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        bool ans = false;
        for(int i = 0; i < 65537; ++ i){
            if(check(i)){
                ans = true;
                break;
            }
        }
        if(ans) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}