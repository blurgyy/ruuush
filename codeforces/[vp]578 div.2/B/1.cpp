#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int T;
int n, m, k;
int h[maxn];

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", h + i);
        }
        bool ans = true;
        for(int i = 1; i < n; ++ i){
            if(h[i+1] - h[i] > k){
                m -= h[i+1] - h[i] - k;
            }
            else {
                m += h[i] - max(0, h[i+1] - k);
            }
            if(m < 0){
                ans = false;
                break;
            }
        }
        if(ans){
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
