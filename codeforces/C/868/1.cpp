#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k;
int minp, know[maxn][5], cnt[5], state[2][5];
set<int> rec;

bool dfs(set<int>::iterator iter = rec.begin(), int count = 1){
    if(count == minp){
        for(int i = 1; i <= k; ++ i){
            if(state[0][i] < state[1][i])return false;
        }
        return true;
    }
    //if(count > minp)return false;
    ++ count;
    int index = *iter;
    set<int>::iterator now = iter ++;
    for(int i = 1; i <= k; ++ i)
        ++ state[know[index][i]][i];
    if(dfs(iter, count))return true;
    for(int i = 1; i <= k; ++ i)
        -- state[know[index][i]][i];
}

int main(){
    while(~scanf("%d%d", &n, &k)){
        minp = INF;
        rec.clear();
        memset(know, 0, sizeof(know));
        memset(cnt, 0, sizeof(cnt));
        memset(state, 0, sizeof(state));
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= k; ++ j){
                scanf("%d", know[i] + j);
                printf("cnt[%d] = %d\n", j, cnt[j]);
                if(know[i][j])continue;
                rec.insert(i);
                cnt[j] += 1;
            }
        }
        for(int i = 1; i <= k; ++ i)
            printf("cnt[%d] = %d, ", i, cnt[i]);
        printf("\n");
        for(int i = 1; i <= k; ++ i)
            minp = min(minp, cnt[i]<<1);
        printf("minp = %d\n", minp);
        if(!minp){
            printf("NO\n");
            continue;
        }
        if(dfs())printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}