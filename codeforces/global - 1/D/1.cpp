#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

int n, m;
int a[maxn];
int cnt[maxn];

int gmin(int pos){return min(cnt[pos], min(cnt[pos+1], cnt[pos+2])); }
void sub(int pos, int val){
    cnt[pos] -= val;
    cnt[pos+1] -= val;
    cnt[pos+2] -= val;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            cnt[a[i]] ++;
        }
        for(int i = 1; i <= m; ++ i){
            printf("%d ", cnt[i]);
        }
        printf("\n");
        int ans = 0;
        for(int i = 1; i <= m; ++ i){
            int cur = gmin(i);
            if(cur){
                ans += cur;
                sub(i, cur);
            }
            ans += cnt[i] / 3;
            cnt[i] %= 3;
        }
        printf("%d\n", ans);
    }
    return 0;
}