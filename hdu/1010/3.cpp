//Nope 
//I'll write again...

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

int n, m, t;
char maze[maxn][maxn];
char ans[2][5] = {"NO", "YES"};
bool res, esc, vis[maxn][maxn];
int sx, sy, ex, ey;

void inline Find(){
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j){
            if(maze[i][j] == 'S'){
                sx = i, sy = j;
            }
            if(maze[i][j] == 'D'){
                ex = i, ey = j;
            }
        }
}

bool inline check(){
    int dis = abs(sx - ex) + abs(sy - ey);
    if(abs(t - dis) & 1)return false;
    return true;
}

bool inline OutofMaze(int x, int y){
    return (x < 1 || x > n || y < 1 || y > m);
}

void inline init(){
    res = false;
    esc = false;
    memset(maze, 0, sizeof(maze));
    memset(vis, 0, sizeof(vis));
    sx = sy = ex = ey = 0;
}

void inline dfs(int x = sx, int y = sy, int time = 0){
    if(OutofMaze(x, y))return;
    if(x == ex && y == ey && time == t){
        res = true;
        esc = true;
        return;
    }
    if(esc)return;
    vis[x][y] = true;
    for(int d = 0; d < 4; ++ d){
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(!vis[nx][ny] && maze[nx][ny] != 'X')
            dfs(nx, ny, time + 1);
    }
    vis[x][y] = false;
}

int main(){
    while(~scanf("%d%d%d", &n, &m, &t) && n || m || t){
        for(int i = 1; i <= n; ++ i)
            scanf("%s", maze[i] + 1);
        Find();
        if(check())dfs();
        printf("%s\n", ans[res]);
    }
    return 0;
}