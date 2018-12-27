#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, m;
int cnt_all, cnt[2][maxn];//0 for rows, 1 for columns
char mp[maxn][maxn];

int main(){
    while(~scanf("%d%d", &n, &m)){
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= n; ++ i)
            scanf("%s", mp[i] + 1);
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= m; ++ j)
                cnt[0][i] += mp[i][j] == '*';
        for(int j = 1; j <= m; ++ j)
            for(int i = 1; i <= n; ++ i){
                cnt[1][j] += mp[i][j] == '*';
                cnt_all += mp[i][j] == '*';
            }
        pair<int, int> ans;
        bool esc = false;
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= m; ++ j)
                if(cnt[0][i] + cnt[1][j] - (mp[i][j] == '*') == cnt_all){
                    ans = make_pair(i, j);
                    esc = true;
                    break;
                }
            if(esc)break;
        }
        if(!ans.first && !ans.second){
            printf("YES\n%d %d\n", ans.first, ans.second);
        }
        else printf("NO\n");
    }
    return 0;
}