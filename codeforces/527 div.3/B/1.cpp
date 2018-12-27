#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
int a[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        sort(a, a + n);
        int ans = 0;
        for(int i = 1; i < n; i += 2){
            ans += a[i] - a[i-1];
        }
        printf("%d\n", ans);
    }
    return 0;
}