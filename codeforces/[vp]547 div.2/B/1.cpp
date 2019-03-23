#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n;
int a[maxn<<1];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        for(int i = n; i < n*2; ++ i){
            a[i] = a[i-n];
        }
        int ans = 0;
        for(int i = 0, cnt = 0; i < n*2; ++ i){
            if(a[i] == 1){
                cnt ++;
                ans = max(ans, cnt);
            }
            else {
                cnt = 0;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
