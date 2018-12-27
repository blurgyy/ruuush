#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10000010;

char s[maxn];
double dp[maxn];

int main(){
    freopen("foreign.in", "r", stdin);
    freopen("foreign.out", "w", stdout);
    while(~scanf("%s", s)){
        int len = strlen(s);
        for(int i = 0; i <= len; ++ i){
            dp[i] = 0;
        }
        double suf = 0;
        ll cntw = (s[len-1] == 'W');
        ll cntc = (s[len-1] == 'C');
        for(int i = len-2; i >= 0; -- i){
            dp[i] = (suf + (double)(s[i] == 'C' ? cntw : cntc)) / (double)(len - i);
            suf += dp[i];
            cntw += (ll)(len - i) * (s[i] == 'W');
            cntc += (ll)(len - i) * (s[i] == 'C');
        }
        printf("%.10f\n", dp[0]);
    }
    return 0;
}