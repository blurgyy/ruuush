#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, a[maxn];
int cnt[maxn], cur, ans;

int main(){
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        cur = -1, ans = 0x3f3f3f3f;
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        int stk[maxn] = {0}, top = 0;
        int rec[maxn];
        memset(rec, -1, sizeof(rec));
        for(int i = n-1; i >= 0; -- i){
            while(top && a[stk[top-1]] < a[i]){
                printf("%d < %d\n", a[stk[top-1]], a[i]);
                rec[stk[--top]] = i;
            }
            stk[top++] = i;
        }
        for(int i = 0; i < n; ++ i)
            printf("%d%c", rec[i], " \n"[i == n-1]);
        for(int i = 0; i < n; ++ i)
            if(rec[i] != -1 && rec[rec[i]] == -1){
                cnt[rec[i]] ++;
            }
        for(int i = 0; i < n; ++ i)
            printf("%d%c", cnt[i], " \n"[i == n-1]);
        for(int i = 0; i < n; ++ i)
            if(cnt[i] > cur){
                ans = a[i];
                cur = cnt[i];
            }
            else if(cnt[i] == cur){
                ans = min(ans, a[i]);
            }
        printf("%d\n", ans);
    }
    return 0;
}