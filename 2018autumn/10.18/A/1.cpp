#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10010;
const int maxk = 1010;
const int mod = 1e9 + 7;

int k, n;
int h[26];
ll ans[maxn];
ll acc[maxn];
char sk[maxk], sn[maxn];

int main(){
    while(~scanf("%d%d", &k, &n)){
        memset(ans, 0, sizeof(ans));
        acc[0] = 0;
        for(int i = 0; i < 26; ++ i){
            scanf("%d", h + i);
        }
        scanf("%s%s", sk + 1, sn + 1);
        for(int i = 1; i <= n; ++ i){
            if(sn[i] == sk[1]){
                ans[i] = 1;
            }
            acc[i] = (acc[i-1] + ans[i]) % mod;
        }
        for(int i = 2; i <= k; ++ i){
            //printf("i = %d\n", i);
            int jmp = h[sk[i-1] - 'A'];

            for(int j = 1; j <= n; ++ j){
                if(sn[j] == sk[i]){
                    ans[j] = j-jmp-1 >= 1 ? acc[j-jmp-1] : 0;
                }
                else {
                    ans[j] = 0;
                }
                //printf("ans[%d] = %d\n", j, ans[j]);
            }

            for(int j = 1; j <= n; ++ j){
                acc[j] = (acc[j-1] + ans[j]) % mod;
            }
        }
        printf("%lld\n", acc[n]);
        //for(int i = 1; i <= n; ++ i)
        //    printf("%lld ", acc[i]);
        //printf("\n");
    }
    return 0;
}

/**

3 10
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
AAA
AAAAAAAAAA

*/