#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;

int main(){
    while(~scanf("%I64d", &n)){
        if(n == 0){
            printf("0\n");
        }
        if(n + 1 & 1){
            printf("%I64d\n", n + 1);
        }
        else 
            printf("%I64d\n", n + 1 >> 1);
    }
    return 0;
}