#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n;
char ans[maxn];

int main(){
    while(~scanf("%d", &n)){
        memset(ans, 0, sizeof(ans));
        ans[0] = 'a';
        ans[1] = 'b';
        ans[2] = 'c';
        ans[3] = 'd';
        for(int i = 4; i < n; ++ i)
            ans[i] = ans[i-4];
        ans[n] = 0;
        printf("%s\n", ans);
    }
    return 0;
}