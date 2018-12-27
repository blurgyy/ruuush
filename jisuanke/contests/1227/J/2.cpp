#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
const int inf = 0x7fffffff;

struct node{
    int x, y;
    node(int _x = 0, int _y = 0){x = _x; y = _y;}
};
int T;
int n, check[maxn][maxn], dp[maxn][maxn];
char mp[maxn][maxn];
bool vis[maxn][maxn], pushed[maxn][maxn];
node Prev[maxn][maxn];

node& get_prev(node &a){
    return Prev[a.x][a.y];
}

void init(){
    memset(Prev, 0, sizeof(Prev));
    memset(check, 0, sizeof(check));
    memset(dp, 0x3f, sizeof(dp));
    memset(vis, false, sizeof(vis));
    memset(pushed, false, sizeof(pushed));
}

int main(){
    //freopen("in.in", "r", stdin);
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
        Prev[start.x][start.y] = node(-1, -1);
        pushed[start.x][start.y] = true;


        //printf("..");
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
                    if(!pushed[nx][ny]){
                        que.push(node(nx, ny));
                        pushed[nx][ny] = true;
                    }
                    for(int it = 0; it < 4; ++ it){
                        int nnx = nx + dx[it];
                        int nny = ny + dy[it];
                        if(vis[nnx][nny]){
                            //printf("check[%d][%d] = %d\n", nnx, nny, check[nnx][nny]);
                            //dp[nx][ny] = min(dp[nx][ny], dp[nnx][nny] + check[nx][ny]);
                            if(dp[nx][ny] < dp[nnx][nny] + check[nx][ny])continue;
                            dp[nx][ny] = dp[nnx][nny] + check[nx][ny];
                            Prev[nx][ny] = node(nnx, nny);
                        }
                    }
                }
            }
        }
        //printf("..");
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
        tmp = mp[start.x][start.y] - '0';
        node now = node(1, pos);
        while(get_prev(now).x != -1 && get_prev(now).y != -1){
            tmp += mp[now.x][now.y] - '0';
            now = get_prev(now);
        }
        ans = max(ans, tmp);
        //printf("%d\n", ans);
        tmp = mp[start.x][start.y] - '0';
        now = node(pos, n);
        while(get_prev(now).x != -1 && get_prev(now).y != -1){
            tmp += mp[now.x][now.y] - '0';
            now = get_prev(now);
        }
        ans = max(ans, tmp);
        pos = n - pos + 1;
        //printf("%d\n", ans);
        tmp = mp[start.x][start.y] - '0';
        now = node(pos, 1);
        while(get_prev(now).x != -1 && get_prev(now).y != -1){
            tmp += mp[now.x][now.y] - '0';
            now = get_prev(now);
        }
        ans = max(ans, tmp);
        //printf("%d\n", ans);
        tmp = mp[start.x][start.y] - '0';
        while(get_prev(now).x != -1 && get_prev(now).y != -1){
            tmp += mp[now.x][now.y] - '0';
            now = get_prev(now);
        }
        ans = max(ans, tmp);
        printf("%d\n", ans);
    }
    return 0;
}
