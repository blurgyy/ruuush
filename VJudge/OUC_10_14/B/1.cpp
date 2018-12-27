#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b;
ll diff, fac;
ll rec[50], p;

int main(){
    while(~scanf("%I64d%I64d", &a, &b)){
        diff = b - a;
        p = 0;
        fac = 1;
        if(diff >= 17){
            printf("0\n");
            continue;
        }
        for(ll i = a+1; i <= b; ++ i)
            rec[p++] = i%10;
        for(int i = 0; i < p; ++ i){
            fac *= rec[i];
            fac %= 10;
        }
        printf("%I64d\n", fac);
    }
    return 0;
}