#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
int sq[maxn];

void init(){
    for(int i = 0; i < maxn; ++ i) sq[i] = i * i;
}

int main(){
    init();
    while(~scanf("%d", &n)){
        int pos = -1;
        for(int i = 1; i < maxn; ++ i){
            if(n > sq[i-1] && n <= sq[i]){
                pos = i;
                break;
            }
        }
        if(pos == -1){
            printf("?\n");
        }
        int m = n - sq[pos-1];
        int ans = 0;
        if(m < pos){
            ans = 2 * pos - 1;
        }
        else {
            ans = 2 * pos;
        }
        printf("%d\n", ans);
    }
    return 0;
}