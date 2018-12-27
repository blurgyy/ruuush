#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100010;

int n, k;
int x[maxn];
int cnt[maxn*10];

int main(){
    while(~scanf("%d%d", &n, &k)){
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= n; ++ i){
            scanf("%d", x + i);
        }
        std::sort(x+1, x+1+n);
        int acc = 1;
        for(int i = 1; i <= n; ++ i){
            if(i < n && x[i+1] == x[i]){
                acc ++;
            }
            if(i == n || x[i+1] != x[i]){
                for(int j = x[i]; j <= k; j += x[i]){
                    cnt[j] += acc;
                }
                acc = 1;
            }
        }
        std::sort(cnt, cnt + 1 + k);
        // for(int i = 1; i <= k; ++ i){
        //  printf("cnt[%d] = %d\n", i, cnt[i]);
        // }
        int maxx = cnt[k];
        int ans = 0;
        for(int i = k; i > 0; -- i){
            if(cnt[i] == maxx){
                ans ++;
            }
            else {
                break;
            }
        }
        printf("%d %d\n", maxx, ans);
    }
    return 0;
}