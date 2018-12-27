#include<bits/stdc++.h>
using namespace std;
const int maxn = 2010;

int a[maxn], n;

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    //printf("%d %d %d\n", gcd(3, 3), gcd(67, 8), gcd(8, 100));
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        int cnt = 0;
        for(int i = 0; i < n; ++ i)
            if(a[i] == 1)++ cnt;
        if(cnt){
            printf("%d\n", n - cnt);
            continue;
        }
        bool esc = false;
        for(int i = 0; i < n; ++ i){
            int top = n - i;
            for(int j = 1; j < top; ++ j){
                a[j-1] = gcd(a[j-1], a[j]);
                if(a[j-1] == 1){
                    cnt = i;
                    esc = true;
                    break;
                }
            }
            if(esc)break;
        }
        if(esc)printf("%d\n", n + cnt);
        else printf("-1\n");
    }
    return 0;
}