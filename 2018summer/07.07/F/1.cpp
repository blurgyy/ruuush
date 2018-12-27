#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int T;
int deg;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &deg);
        if(deg >= 185){
            deg -= 180;
        }
        int ans = deg / 10;
        if(deg % 10 >= 5){
            ++ ans;
        }
        if(ans == 0)ans = 18;
        printf("%02d\n", ans);
    }
    return 0;
}