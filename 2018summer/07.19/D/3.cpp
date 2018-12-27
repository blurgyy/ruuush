#include <cstdio>
#include <cstring>
//#include <windows.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int INT_MAX = 2147483647;
const ll inf = 0x3f3f3f3f;

int n;
ll a[maxn], b[maxn];

int main(){
    //freopen("73.in", "r", stdin);
    while(~scanf("%d", &n)){
    //scanf("%d", &n);{
        for(int i = 0; i < n; ++ i){
            scanf("%lld", a + i);
        }
        b[0] = 0;
        ll min_o = inf, min_e = 0;
        for(int i = 1; i <= n; ++ i){
            b[i] = a[i-1] - b[i-1];
            if(i & 1){
                min_o = min(min_o, b[i]);
            }
            else {
                min_e = min(min_e, b[i]);
            }
        }
        ll ans = max((min_e + min_o + 1), 0LL);
        while(ans >= INT_MAX){};
        //printf("min_e = %d, min_o = %d, ans = %d\n", min_e, min_o, ans);
        /*for(int i = 0; i <= n; ++ i){
            printf("%d ", b[i]);
        }
        printf("\n");*/
        printf("%lld\n", ans);
    }
    //system("pause");
    return 0;
}

/** 

6
12 5 7 7 8 4

*/