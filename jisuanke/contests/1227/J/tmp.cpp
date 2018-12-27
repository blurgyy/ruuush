#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
const int inf = 0x7fffffff;

struct node{
    int x, y;
    node(int _x, int _y){x = _x; y = _y;}
};
int T;
int n, check[maxn][maxn], dp[maxn][maxn];
char mp[maxn][maxn];
bool vis[maxn][maxn];
vector<node> path[maxn][maxn];

void init(){
    for(int i = 0; i < maxn; ++ i)
        for(int j = 0; j < maxn; ++ j)
            path[i][j].clear();
    memset(check, 0, sizeof(check));
    memset(dp, 0x3f, sizeof(dp));
    memset(vis, false, sizeof(vis));
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        //printf("n = %d\n", n);
        for(int i = 1; i <= n; ++ i)
            scanf("%s", mp[i] + 1);
        //printf("test: %s\n", mp[2]);
        //printf("mpp[1][1] = %c,\n", mp[1][1]);
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j){
                check[i][j] += (mp[i][j] - '0' + mp[n-i+1][n-j+1] - '0' + mp[j][n-i+1] - '0' + mp[n-j+1][i] - '0');
                //printf("i = %d, j = %d, %d %d %d %d\n", i, j, mp[i][j] - '0', mp[n-i+1][n-j+1] - '0', mp[j][n-i+1] - '0', mp[n-j+1][i] - '0');
            }
/*
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j)
                printf("%d ", check[i][j]);
            printf("\n");
        }
*/
        node start(n+1>>1, n+1>>1);
        dp[n+1>>1][n+1>>1] = check[n+1>>1][n+1>>1];
        queue<node> que;
        que.push(start);
        path[n+1>>1][n+1>>1].push_back(start);
        while(que.size()){
            //printf("size = %d\n", que.size());
            node now = que.front();
            que.pop();
            vis[now.x][now.y] = true;
            for(int d = 0; d < 4; ++ d){
                int nx = now.x + dx[d];
                int ny = now.y + dy[d];
                if(nx == 0 || nx == n+1 || ny == 0 || ny == n+1)
                    continue;
                if(!vis[nx][ny]){
                    que.push(node(nx, ny));
                    for(int it = 0; it < 4; ++ it){
                        int nnx = nx + dx[it];
                        int nny = ny + dy[it];
                        if(vis[nnx][nny]){
                            //printf("check[%d][%d] = %d\n", nnx, nny, check[nnx][nny]);
                            //dp[nx][ny] = min(dp[nx][ny], dp[nnx][nny] + check[nx][ny]);
                            if(dp[nx][ny] < dp[nnx][nny] + check[nx][ny])continue;
                            dp[nx][ny] = dp[nnx][nny] + check[nx][ny];
                            path[nx][ny] = path[nnx][nny];
                            path[nx][ny].push_back(node(nx, ny));
                        }
                    }
                }
            }
        }
/*
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j)
                printf("%d ", dp[i][j]);
            printf("\n");
        }
*/

        int tmp = inf, pos = -1, ans = -1;
        for(int i = 1; i <= n; ++ i)
            if(tmp > dp[1][i]){
                tmp = dp[1][i];
                pos = i;
            }
/*
        for(int i = 0; i < path[1][pos].size(); ++ i)
            printf("%d %d\n", path[1][pos][i]);
*/
        tmp = 0;
        for(int i = 0; i < path[1][pos].size(); ++ i)
            tmp += mp[path[1][pos][i].x][path[1][pos][i].y] - '0';
        ans = max(ans, tmp);
        //printf("%d\n", ans);
        tmp = 0;
        for(int i = 0; i < path[pos][n].size(); ++ i)
            tmp += mp[path[pos][n][i].x][path[pos][n][i].y] - '0';
        ans = max(ans, tmp);
        pos = n - pos + 1;
        //printf("%d\n", ans);
        tmp = 0;
        for(int i = 0; i < path[pos][1].size(); ++ i)
            tmp += mp[path[pos][1][i].x][path[pos][1][i].y] - '0';
        ans = max(ans, tmp);
        //printf("%d\n", ans);
        tmp = 0;
        for(int i = 0; i < path[pos][1].size(); ++ i)
            tmp += mp[path[n][pos][i].x][path[n][pos][i].y] - '0';
        ans = max(ans, tmp);
        printf("%d\n", ans);
    }
    return 0;
}
