#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int q, n;

int main(){
    while(~scanf("%d", &q)){
        while(q--){
            int add = 0;
            scanf("%d", &n);
            if(n == 9){
                printf("1\n");
                continue;
            }
            if(n < 4){
                printf("-1\n");
                continue;
            }
            if(n&1){
                n -= 9;
                add++;
            }
            if(n < 4){
                printf("-1\n");
                continue;
            }
            int mod = n % 4;
            if(!mod){
                printf("%d\n", n/4 + add);
                continue;
            }
            else{
                n -= 6;
                add++;
                printf("%d\n", n/4 + add);
                continue;
            }
        }
    }
    return 0;
}