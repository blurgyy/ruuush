#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
int s[maxn], d[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i)
            scanf("%d%d", s + i, d + i);
        int cur = 1, i;
        for(i = 1; i < 10000000 && cur != n+1; ++ i){
            if(i - s[cur] >= 0 && (i - s[cur]) % d[cur] == 0){
                //printf("i = %d, cur = %d\n", i, cur);
                cur ++;
            }
        }
        printf("%d\n", i-1);
    }
    return 0;
}
