#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n;
int c[maxn], t[maxn];
int ca[maxn], ta[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", c + i);
        }
        for(int i = 0; i < n; ++ i){
            scanf("%d", t + i);
        }
        for(int i = 1; i < n; ++ i){
            ca[i] = (c[i] - c[i-1]);
            ta[i] = (t[i] - t[i-1]);
        }
        sort(ca+1, ca+1 + n);
        sort(ta+1, ta+1 + n);
        bool ans = true;
        for(int i = 1; i < n; ++ i){
            if(ca[i] != ta[i]) {
                ans = false;
                break;
            }
        }
        if(c[0] != t[0] || c[n-1] != t[n-1]) ans = false;
        if(ans) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}