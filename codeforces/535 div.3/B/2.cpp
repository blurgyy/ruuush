/// go to 1.cpp

#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;
const int inf = 0x3f3f3f3f;

int n;
int d[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", d + i);
        }
        sort(d+1, d+1 + n);
        int ans1 = d[n];
        for(int i = n; i ; -- i){
            if(i < n && d[i] == d[i+1]){
                continue;
            }
            if(ans1 % d[i] == 0){
                d[i] = -inf;
            }
        }
        sort(d+1, d+1 + n);
        int ans2 = -1;
        for(int i = 1; i <= n; ++ i){
            ans2 = max(ans2, d[i]);
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}