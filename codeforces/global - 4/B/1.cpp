#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;

char s[maxn];
int wcnt[maxn];

int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        memset(wcnt, 0, sizeof(wcnt));
        for(int i = 1; i < len; ++ i){
            if(s[i-1] == 'v' && s[i] == 'v'){
                wcnt[i] ++;
            }
        }
        for(int i = 1; i < len; ++ i){
            wcnt[i] += wcnt[i-1];
        }
        ll ans = 0;
        for(int i = 0; i < len; ++ i){
            if(s[i] == 'o'){
                ans += 1ll * wcnt[i] * (wcnt[len-1] - wcnt[i]);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
