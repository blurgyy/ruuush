//....
//TLE because of dfs...
//I should have used bfs
///ok let's write another one right now

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

int n, m, t;
char maze[maxn][maxn];
char ans[2][5] = {"NO", "YES"};
bool vis[maxn][maxn];
int res;

void dfs(int x, int y, int time = 0){
    if(res)return;
    if(maze[x][y] == 'D' && time == t){
        res = true;
        return;
    }
    if(time > t)return;
    for(int d = 0; d < 4; ++ d){
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(maze[nx][ny] != 'X' && !vis[nx][ny]){
            vis[nx][ny] = true;
            dfs(nx, ny, time+1);
            vis[nx][ny] = false;
        }
    }
}

void init(){
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i <= n+1; ++ i)
        maze[i][0] = maze[i][m+1] = 'X';
    for(int j = 1; j <= m; ++ j)
        maze[0][j] = maze[n+1][j] = 'X';
    res = 0;
}

int main(){
    while(~scanf("%d%d%d", &n, &m, &t) && n || m || t){
        for(int i = 1; i <= n; ++ i)
            scanf("%s", maze[i] + 1);
        init();
        int sx = 0, sy = 0;
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= m; ++ j)
                if(maze[i][j] == 'S'){
                    sx = i, sy = j;
                    break;
                }
        dfs(sx, sy);
        printf("%s\n", ans[res]);
    }
    return 0;
}