#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
vector<int> E[maxn], leaves;
int leafcnt;

void dfs(int now = 1, int prev = -1){
    bool leaf = true;
    if(now * 2 <= n){
        leaf = false;
        dfs(now * 2, now);
    }
    if(now * 2 + 1 <= n){
        dfs(now * 2 + 1, now);
    }
    if(leaf){
        leaves.push_back(now);
    }
    leafcnt += leaf;
}

void init(){
    leaves.clear();
    leafcnt = 0;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        dfs();
        for(int i = 1, cnt = 0; cnt < n-1; ++ i){
            if(i * 2 <= n){
                printf("%d %d\n", i, i * 2);
                cnt ++;
            }
            if(cnt == n-1){
                break;
            }
            if(i * 2 + 1 <= n){
                printf("%d %d\n", i, i * 2 + 1);
                cnt ++;
            }
        }
        int edgecnt = n - 1 + (leafcnt + 1) / 2;
        printf("%d\n", edgecnt);
        for(int i = 1; i < leaves.size(); ++ i){
            
        }
    }
    return 0;
}
