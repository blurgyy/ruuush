#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10010;

int x, d, p;
ll a[maxn], rec[70];

void init(){
    memset(a, 0, sizeof(a));
    p = 1;
    a[0] = 1;
    rec[0] = 0;
}

int main(){
    for(int i = 1; i < 70; ++ i)
        rec[i] = pow(2, i) - 1;
    for(int i = 0; i < 64; ++ i)
        printf("%lld\n", rec[i]);
    while(~scanf("%d%d", &x, &d)){
        init();
        x -= 1;

        while(x){

        }
    }
    return 0;
}