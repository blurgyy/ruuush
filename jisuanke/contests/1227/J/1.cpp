#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

struct node{
    int x, y;
    node(int _x, int _y){x = _x; y = _y;}
};
int T;
int n, check[maxn][maxn], dp[maxn][maxn];
char mp[maxn][maxn];
bool vis[maxn][maxn];

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        printf("n = %d\n", n);
        for(int i = 1; i <= n; ++ i)
            scanf("%s", mp[i] + 1);
        //printf("test: %s\n", mp[2]);
        //printf("mpp[1][1] = %c,\n", mp[1][1]);
        memset(check, 0, sizeof(check));
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j){
                check[i][j] += (mp[i][j] - '0' + mp[n-i+1][n-j+1] - '0' + mp[j][n-i+1] - '0' + mp[n-j+1][i] - '0');
                //printf("i = %d, j = %d, %d %d %d %d\n", i, j, mp[i][j] - '0', mp[n-i+1][n-j+1] - '0', mp[j][n-i+1] - '0', mp[n-j+1][i] - '0');
            }

        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j)
                printf("%d ", check[i][j]);
            printf("\n");
        }

        memset(dp, 0x3f, sizeof(dp));
        memset(vis, false, sizeof(vis));
        node start(n+1>>1, n+1>>1);
        dp[n+1>>1][n+1>>1] = check[n+1>>1][n+1>>1];
        queue<node> que;
        que.push(start);
        while(que.size()){
            if(!(que.size()%100))printf("size = %d\n", que.size());
            node now = que.front();
            vis[now.x][now.y] = true;
            for(int d = 0; d < 4; ++ d){
                int nx = now.x + dx[d];
                int ny = now.y + dy[d];
                if(nx == 0 || nx == n+1 || ny == 0 || ny == n+1)
                    continue;
                if(!vis[nx][ny]){
                    que.push(node(nx, ny));
                    for(int it = 0; it < 4; ++ it){
                        int nnx = nx + dx[d];
                        int nny = ny + dy[d];
                        if(vis[nnx][nny])
                            dp[nx][ny] = min(dp[nx][ny], dp[nnx][nny]);
                    }
                }
            }
        }
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j)
                printf("%d ", dp[i][j]);
            printf("\n");
        }
    }
    return 0;
}
