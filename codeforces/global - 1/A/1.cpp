#include <bits/stdc++.h>
using namespace std;

int a, b, k;

int main(){
    while(~scanf("%d%d", &b, &k)){
        int ans = 0;
        if(b & 1){
            while(k --){
                scanf("%d", &a);
                ans += a & 1;
            }
            printf("%s\n", (ans & 1) ? "odd" : "even");
        }
        else {
            while(k --){
                scanf("%d", &a);
                if(k == 0) ans = a;
            }
            printf("%s\n", (ans & 1) ? "odd" : "even");
        }
    }
    return 0;
}