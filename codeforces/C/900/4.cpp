#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, a[maxn], cnt[maxn];
int stk[maxn], top, rec[maxn];

void inline init(){
    memset(rec, -1, sizeof(rec));
    memset(cnt, 0, sizeof(cnt));
    top = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        for(int i = n-1; i >= 0; -- i){
            while(top && a[i] > a[stk[top-1]]){
                rec[stk[--top]] = i;
                printf("%d > %d is true\n", a[i], a[stk[top]]);
            }
            stk[top++] = i;
        }
        for(int i = 0; i < n; ++ i){
            if(rec[i] != -1 && rec[rec[i]] == -1)
                cnt[rec[i]] ++;
        }
        for(int i = 0; i < n; ++ i)
            printf("rec[%d] = %d, cnt[%d] = %d\n", i, rec[i], i, cnt[i]);
        int cur = 0, ans = 0;
        for(int i = 0; i < n; ++ i)
            if(cnt[i] > cur){
                ans = a[i];
                cur = cnt[i];
            }
            else if(cnt[i] == cur)
                ans = min(ans, a[i]);
        printf("%d\n", ans);
    }
    return 0;
}